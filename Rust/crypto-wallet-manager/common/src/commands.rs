use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use rust_decimal::Decimal;

use crate::models::offering::Offering;

#[derive(Debug, Serialize, Deserialize)]
pub enum ClientCommand {
    Register { username: String, password: String},
    Login { username: String, password: String},
    Deposit  { amount: Decimal },
    Buy { asset_id: String, amount: Decimal},
    Sell { asset_id: String },
    ListOfferings,
    GetProfile,
    GetWalletSummary,
    GetWalletOverallSummary,
}

#[derive(Debug, Serialize, Deserialize)]
pub enum ServerResponse {
    Message(String),
    Error(String),
    Offerings(Vec<Offering>),
    WalletSummary {
        usd_balance: f64,
        investments: HashMap<String, f64>
    }
}
