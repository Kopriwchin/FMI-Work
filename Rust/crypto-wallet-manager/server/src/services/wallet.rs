use rust_decimal::Decimal;
use common::models::user::User;
use common::models::transaction::{Transaction, TransactionType};

pub fn deposit(
    user: &mut User,
    amount: Decimal,
) {

    user.wallet.balance += amount;

    let tx = Transaction::new(
        user.id.clone(),
        "USD".into(),
        amount,
        TransactionType::Deposit,
    );

    user.wallet.transactions.push(tx);
}

pub fn buy(
    user: &mut User,
    asset_id: String,
    price: Decimal,
    amount_usd: Decimal,
) -> Result<(), String> {

    if user.wallet.balance < amount_usd {
        return Err("Insufficient funds".into());
    }

    let quantity = amount_usd / price;

    user.wallet.balance -= amount_usd;

    let entry = user.wallet
        .assets
        .entry(asset_id)
        .or_insert(Decimal::ZERO);

    *entry += quantity;

    Ok(())
}

pub fn sell(
    user: &mut User,
    asset_id: String,
    price: Decimal,
) -> Result<(), String> {

    let quantity = user.wallet
        .assets
        .remove(&asset_id)
        .ok_or("Asset not owned")?;

    let usd = quantity * price;

    user.wallet.balance += usd;

    Ok(())
}
