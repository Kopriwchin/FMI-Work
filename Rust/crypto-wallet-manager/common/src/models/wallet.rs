use std::collections::HashMap;
use rust_decimal::Decimal;
use serde::Serialize;
use serde::Deserialize;

use crate::models::transaction::Transaction;

#[derive(Serialize, Deserialize, Clone)]
pub struct Wallet {
    pub balance: Decimal,
    pub assets: HashMap<String, Decimal>,
    pub transactions: Vec<Transaction>
}