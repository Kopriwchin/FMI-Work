use std::collections::HashMap;
use rust_decimal::Decimal;
use serde::Serialize;
use serde::Deserialize;
use uuid::Uuid;
use crate::models::wallet::Wallet;

#[derive(Serialize, Deserialize, Clone)]
pub struct User {
    pub id: String,
    pub username: String,
    pub password_hash: String,
    pub wallet: Wallet,
}

impl User {
    pub fn new(username: String, password_hash: String) -> Self {
        Self {
            id: Uuid::new_v4().to_string(),
            username,
            password_hash,
            wallet: Wallet {
                balance: Decimal::ZERO,
                assets: HashMap::new(),
                transactions: Vec::new(),
            },
        }
    }
}