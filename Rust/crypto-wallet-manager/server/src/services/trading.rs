use rust_decimal::Decimal;
use crate::state::AppState;
use common::models::transaction::{Transaction, TransactionType};

pub fn buy(
    state: &AppState,
    user_id: &str,
    asset: &str,
    usd_amount: Decimal,
    price: Decimal,
) -> Result<(), String> {

    let user =
        users.values_mut()
            .find(|u| u.id == user_id)
            .ok_or("user not found")?;

    if user.wallet.balance < usd_amount {
        return Err("insufficient balance".into());
    }

    let qty: Decimal = usd_amount / price;

    user.wallet.balance -= usd_amount;

    let tx = Transaction::new(
        user.id.clone(),
        asset.into(),
        qty,
        TransactionType::Buy,
    );

    user.wallet.transactions.push(tx);

    Ok(())
}
