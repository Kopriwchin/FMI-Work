use rust_decimal::Decimal;
use std::str::FromStr;
use uuid::Uuid;
use sqlx::{Sqlite, Transaction};

use crate::state::AppState;
use common::commands::{HoldingDto, TransactionDto, WalletSummaryDto};

pub async fn buy(
    state: &AppState,
    user_id: &str,
    asset_id: &str,
    usd_amount: Decimal,
) -> Result<(), String> {

    let price = fetch_crypto_price(state, asset_id).await?;

    let quantity: Decimal = usd_amount / price;

    let mut tx: Transaction<'_, Sqlite> =
        state.db.begin()
            .await
            .map_err(|_| "DB error")?;

    let balance: Decimal =
        get_wallet_balance(&mut tx, user_id).await?;

    if balance < usd_amount {
        return Err("Insufficient funds".into());
    }

    update_wallet_balance(
        &mut tx,
        user_id,
        balance - usd_amount
    ).await?;

    upsert_holding(
        &mut tx,
        user_id,
        asset_id,
        quantity
    ).await?;

    insert_transaction(
        &mut tx,
        user_id,
        asset_id,
        quantity,
        "BUY"
    ).await?;

    tx.commit()
        .await
        .map_err(|_| "Commit failed")?;

    Ok(())
}

async fn fetch_crypto_price(
    state: &AppState,
    asset_id: &str,
) -> Result<Decimal, String> {

    let asset = state.coin_service
        .get_asset(asset_id)
        .await
        .map_err(|_| "Asset fetch failed")?;

    if asset.type_is_crypto != Some(1) {
        return Err("Not crypto".into());
    }

    let price_f64 = asset.price_usd
        .ok_or("No price")?;

    let price: Decimal =
        Decimal::from_str(&price_f64.to_string())
            .map_err(|_| "Invalid price".to_string())?;

    Ok(price)

}

async fn get_wallet_balance(
    tx: &mut Transaction<'_, Sqlite>,
    user_id: &str,
) -> Result<Decimal, String> {

    let row = sqlx::query!(
        "SELECT balance FROM wallets WHERE user_id = ?1",
        user_id
    )
        .fetch_one(&mut **tx)
        .await
        .map_err(|_| "Wallet not found")?;

    let balance: Decimal =
        Decimal::from_str(&row.balance.to_string())
            .map_err(|_| "Invalid price".to_string())?;

    Ok(balance)

}

async fn update_wallet_balance(
    tx: &mut Transaction<'_, Sqlite>,
    user_id: &str,
    new_balance: Decimal,
) -> Result<(), String> {

    let balance_string: String = new_balance.to_string();

    sqlx::query!(
        "UPDATE wallets SET balance = ?1 WHERE user_id = ?2",
        balance_string,
        user_id
    )
    .execute(&mut **tx)
    .await
    .map_err(|_| "Balance update failed")?;

    Ok(())
}

async fn upsert_holding(
    tx: &mut Transaction<'_, Sqlite>,
    user_id: &str,
    asset_id: &str,
    quantity: Decimal,
) -> Result<(), String> {

    let existing = sqlx::query!(
        "SELECT amount FROM holdings WHERE user_id = ?1 AND asset_id = ?2",
        user_id,
        asset_id
    )
        .fetch_optional(&mut **tx)
        .await
        .map_err(|_| "Holding query failed")?;

    if let Some(row) = existing {

        let current =
            Decimal::from_str(&row.amount)
                .map_err(|_| "Invalid holding amount")?;

        let new_amount =
            (current + quantity).to_string();

        sqlx::query!(
            "UPDATE holdings SET amount = ?1 WHERE user_id = ?2 AND asset_id = ?3",
            new_amount,
            user_id,
            asset_id
        )
            .execute(&mut **tx)
            .await
            .map_err(|_| "Holding update failed")?;

    } else {
        let quantity_string: String = quantity.to_string();

        sqlx::query!(
            "INSERT INTO holdings (user_id, asset_id, amount)
             VALUES (?1, ?2, ?3)",
            user_id,
            asset_id,
            quantity_string
        )
            .execute(&mut **tx)
            .await
            .map_err(|_| "Holding insert failed")?;
    }

    Ok(())
}

async fn insert_transaction(
    tx: &mut Transaction<'_, Sqlite>,
    user_id: &str,
    asset_id: &str,
    quantity: Decimal,
    tx_type: &str,
) -> Result<(), String> {

    let id: String = Uuid::new_v4().to_string();
    let qty_string: String = quantity.to_string();
    let tx_type_string: String = tx_type.to_string();

    sqlx::query!(
        "
        INSERT INTO transactions
        (id, user_id, asset_id, amount, type)
        VALUES (?1, ?2, ?3, ?4, ?5)
        ",
        id,
        user_id,
        asset_id,
        qty_string,
        tx_type_string
    )
        .execute(&mut **tx)
        .await
        .map_err(|_| "Transaction insert failed".to_string())?;

    Ok(())
}

pub async fn transaction_history(
    state: &AppState,
    user_id: &str,
    page: i64,
    page_size: i64,
) -> Result<Vec<TransactionDto>, String> {

    if page < 1 || page_size < 1 || page_size > 200 {
        return Err("Invalid pagination".to_string());
    }

    let offset: i64 = (page - 1) * page_size;

    let rows = sqlx::query!(
        "
        SELECT id, asset_id, amount, type, created_at
        FROM transactions
        WHERE user_id = ?1
        ORDER BY created_at DESC
        LIMIT ?2 OFFSET ?3
        ",
        user_id,
        page_size,
        offset
    )
        .fetch_all(&state.db)
        .await
        .map_err(|_| "Query failed".to_string())?;

    let mut result: Vec<TransactionDto> = Vec::new();

    for row in rows {
        let amount: Decimal = Decimal::from_str(&row.amount)
            .map_err(|_| "Invalid tx amount".to_string())?;

        result.push(TransactionDto {
            id: row.id,
            asset_id: row.asset_id,
            amount,
            tx_type: row.r#type,
            created_at: row.created_at.to_string(),
        });
    }

    Ok(result)
}


pub async fn deposit(
    state: &AppState,
    user_id: &str,
    amount: Decimal,
) -> Result<(), String> {

    if amount <= Decimal::ZERO {
        return Err("Amount must be positive".into());
    }

    let mut tx: Transaction<'_, Sqlite> =
        state.db.begin().await.map_err(|_| "DB error".to_string())?;

    let balance = get_wallet_balance(&mut tx, user_id).await?;

    let new_balance: Decimal = balance + amount;

    update_wallet_balance(&mut tx, user_id, new_balance).await?;

    tx.commit().await.map_err(|_| "Commit failed".to_string())?;

    Ok(())
}

pub async fn sell_all(
    state: &AppState,
    user_id: &str,
    asset_id: &str,
) -> Result<(), String> {

    let asset = state.coin_service
        .get_asset(asset_id)
        .await
        .map_err(|_| "Asset fetch failed".to_string())?;

    if asset.type_is_crypto != Some(1) {
        return Err("Not crypto".into());
    }

    let price_f64 = asset.price_usd.ok_or("No price".to_string())?;
    let price: Decimal = Decimal::from_str(&price_f64.to_string())
        .map_err(|_| "Invalid price".to_string())?;

    let mut tx: Transaction<'_, Sqlite> =
        state.db.begin().await.map_err(|_| "DB error".to_string())?;

    let holding = sqlx::query!(
        "SELECT amount FROM holdings WHERE user_id = ?1 AND asset_id = ?2",
        user_id,
        asset_id
    )
        .fetch_optional(&mut *tx)
        .await
        .map_err(|_| "Holding query failed".to_string())?;

    let holding_row = holding.ok_or("Asset not owned".to_string())?;

    let qty: Decimal = Decimal::from_str(&holding_row.amount)
        .map_err(|_| "Invalid holding amount".to_string())?;

    if qty <= Decimal::ZERO {
        return Err("Invalid holding quantity".into());
    }

    let usd_value: Decimal = qty * price;

    sqlx::query!(
        "DELETE FROM holdings WHERE user_id = ?1 AND asset_id = ?2",
        user_id,
        asset_id
    )
        .execute(&mut *tx)
        .await
        .map_err(|_| "Holding delete failed".to_string())?;

    let balance = get_wallet_balance(&mut tx, user_id).await?;
    let new_balance: Decimal = balance + usd_value;
    update_wallet_balance(&mut tx, user_id, new_balance).await?;

    // 4) Insert transaction
    insert_transaction(&mut tx, user_id, asset_id, qty, "SELL").await?;

    tx.commit().await.map_err(|_| "Commit failed".to_string())?;

    Ok(())
}

pub async fn wallet_summary(
    state: &AppState,
    user_id: &str,
) -> Result<WalletSummaryDto, String> {

    let rows = sqlx::query!(
        "
        SELECT w.balance as balance, h.asset_id as asset_id, h.amount as amount
        FROM wallets w
        LEFT JOIN holdings h
            ON w.user_id = h.user_id
        WHERE w.user_id = ?1
        ",
        user_id
    )
        .fetch_all(&state.db)
        .await
        .map_err(|_| "Query failed".to_string())?;

    if rows.is_empty() {
        return Err("Wallet not found".to_string());
    }

    let balance_string: String = rows[0].balance.clone();
    let balance_usd: Decimal =
        Decimal::from_str(&balance_string)
            .map_err(|_| "Invalid balance".to_string())?;

    let mut holdings: Vec<HoldingDto> = Vec::new();

    for row in rows {
        if let (Some(asset_id), Some(amount_str)) = (row.asset_id, row.amount) {
            let amount: Decimal =
                Decimal::from_str(&amount_str)
                    .map_err(|_| "Invalid holding amount".to_string())?;

            holdings.push(HoldingDto { asset_id, amount });
        }
    }

    Ok(WalletSummaryDto {
        balance_usd,
        holdings,
    })
}

pub async fn portfolio_value(
    state: &AppState,
    user_id: &str,
) -> Result<Decimal, String> {

    let rows = sqlx::query!(
        "
        SELECT h.asset_id, h.amount, w.balance
        FROM wallets w
        LEFT JOIN holdings h
            ON w.user_id = h.user_id
        WHERE w.user_id = ?1
        ",
        user_id
    )
        .fetch_all(&state.db)
        .await
        .map_err(|_| "Query failed")?;

    if rows.is_empty() {
        return Err("User not found".into());
    }

    let mut total = Decimal::from_str(&rows[0].balance)
        .map_err(|_| "Invalid balance")?;

    for row in rows {

        if let (Some(asset_id), Some(amount_str)) =
            (row.asset_id.clone(), row.amount.clone()) {

            let amount =
                Decimal::from_str(&amount_str)
                    .map_err(|_| "Invalid amount")?;

            let asset = state.coin_service
                .get_asset(&asset_id)
                .await
                .map_err(|_| "Asset fetch failed")?;

            let price_f64 =
                asset.price_usd.ok_or("No price")?;

            let price =
                Decimal::from_str(&price_f64.to_string())
                    .map_err(|_| "Invalid price")?;

            total += amount * price;
        }
    }

    Ok(total)
}