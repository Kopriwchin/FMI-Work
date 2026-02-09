use serde::{Deserialize, Serialize};
use std::collections::HashMap;

#[derive(Debug, Serialize, Deserialize)]
pub enum ClientCommand {
    Register { username: String, password: String},
    Login { username: String, password: String},
    DepositMoney { amount: f64 },
    ListOfferings,
    Buy { offering: String, money: f64 },
    Sell { offering: String },
    GetWalletSummary,
    GetWalletOverallSummary,
}

#[derive(Debug, Serialize, Deserialize)]
pub enum ServerResponse {
    Ok(String),
    Error(String),
    Offerings(Vec<String>),
    WalletSummary {
        usd_balance: f64,
        investments: HashMap<String, f64>
    }
}
