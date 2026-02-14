use crate::state::AppState;
use rust_decimal::Decimal;
use std::str::FromStr;
use std::time::{SystemTime, UNIX_EPOCH};

const CACHE_SECONDS: i64 = 30 * 60;
const MAX_OFFERINGS: usize = 50;

pub async fn get_cached_assets(
    state: &AppState,
) -> Result<Vec<(String, String, Decimal)>, String> {

    let now: i64 = unix_now_seconds()?;

    let should_refresh: bool = should_refresh_cache(state, now).await?;

    if should_refresh {
        refresh_cache(state, now).await?;
    }

    read_cache(state).await
}

fn unix_now_seconds() -> Result<i64, String> {
    Ok(
        SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .map_err(|_| "Time error".to_string())?
            .as_secs() as i64
    )
}

async fn should_refresh_cache(
    state: &AppState,
    now: i64,
) -> Result<bool, String> {

    let row = sqlx::query!(
        "SELECT MAX(last_updated) as last_updated FROM cached_assets"
    )
        .fetch_one(&state.db)
        .await
        .map_err(|_| "Cache check failed".to_string())?;

    Ok(match row.last_updated {
        Some(ts) => now - ts > CACHE_SECONDS,
        None => true,
    })
}

async fn refresh_cache(
    state: &AppState,
    now: i64,
) -> Result<(), String> {

    let assets = state.coin_service
        .get_assets()
        .await
        .map_err(|_| "Failed to fetch assets from CoinAPI".to_string())?;

    let crypto_assets = assets
        .into_iter()
        .filter(|a| a.type_is_crypto == Some(1))
        .filter(|a| a.price_usd.is_some())
        .take(MAX_OFFERINGS)
        .collect::<Vec<_>>();

    let mut tx = state.db.begin()
        .await
        .map_err(|_| "DB error".to_string())?;

    sqlx::query!("DELETE FROM cached_assets")
        .execute(&mut *tx)
        .await
        .map_err(|_| "Cache clear failed".to_string())?;

    for a in crypto_assets {
        let asset_id: String = a.asset_id;
        let name: String = a.name.unwrap_or_default();
        let price_string: String = a.price_usd.unwrap().to_string();

        sqlx::query!(
            "
            INSERT INTO cached_assets (asset_id, name, price_usd, last_updated)
            VALUES (?1, ?2, ?3, ?4)
            ",
            asset_id,
            name,
            price_string,
            now
        )
            .execute(&mut *tx)
            .await
            .map_err(|_| "Cache insert failed".to_string())?;
    }

    tx.commit()
        .await
        .map_err(|_| "Commit failed".to_string())?;

    Ok(())
}

async fn read_cache(
    state: &AppState,
) -> Result<Vec<(String, String, Decimal)>, String> {

    let rows = sqlx::query!(
        "
        SELECT asset_id, name, price_usd
        FROM cached_assets
        ORDER BY asset_id
        LIMIT ?1
        ",
        MAX_OFFERINGS as i64
    )
        .fetch_all(&state.db)
        .await
        .map_err(|_| "Cache read failed".to_string())?;

    let mut result: Vec<(String, String, Decimal)> = Vec::new();

    for row in rows {
        let asset_id: String = row.asset_id; // NOT NULL (PRIMARY KEY)
        let name: String = row.name.unwrap_or_default();
        let price_str: String = row.price_usd.ok_or_else(|| "Missing price_usd".to_string())?;

        let price: Decimal = Decimal::from_str(&price_str)
            .map_err(|_| "Invalid cached price".to_string())?;

        result.push((asset_id, name, price));
    }

    Ok(result)
}
