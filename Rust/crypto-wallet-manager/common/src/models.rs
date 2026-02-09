use serde::{Deserialize, Serialize};
use std::collections::HashMap;

#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Wallet {
    pub usd_balance: f64,
    pub investments: HashMap<String, f64>,
}

impl Wallet {
    pub fn new() -> Self {
        Self {
            usd_balance: 0.0,
            investments: HashMap::new(),
        }
    }
}

#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct User {
    pub username: String,
    pub password_hash: String,
    pub wallet: Wallet,
}

impl User {
    pub fn new(username: String, password_hash: String) -> Self {
        Self {
            username,
            password_hash,
            wallet: Wallet::new(),
        }
    }
}