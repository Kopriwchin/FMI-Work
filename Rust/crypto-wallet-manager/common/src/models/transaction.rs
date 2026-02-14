use rust_decimal::Decimal;
use serde::{Serialize, Deserialize};
use uuid::Uuid;

#[derive(Serialize, Deserialize, Clone)]
pub enum TransactionType {
    Deposit,
    Withdraw,
    Buy,
    Sell,
}

#[derive(Serialize, Deserialize, Clone)]
pub struct Transaction {
    pub id: String,
    pub user_id: String,
    pub asset: String,
    pub amount: Decimal,
    pub ttype: TransactionType,
}

impl Transaction {

    pub fn new(
        user_id: String,
        asset: String,
        amount: Decimal,
        ttype: TransactionType,
    ) -> Self {

        Self {
            id: Uuid::new_v4().to_string(),
            user_id,
            asset,
            amount,
            ttype,
        }
    }
}