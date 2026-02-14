use serde::{Deserialize, Serialize};
use rust_decimal::Decimal;
use crate::models::offering::Offering;

#[derive(Debug, Serialize, Deserialize)]
pub enum ClientCommand {
    Register { username: String, password: String },
    Login { username: String, password: String },

    Deposit { amount: Decimal },
    Buy { asset_id: String, amount: Decimal },
    Sell { asset_id: String },

    ListOfferings,
    GetPrice { asset_id: String },

    GetProfile,
    GetWalletSummary,
    GetWalletOverallSummary,
    GetTransactionHistory { page: i64, page_size: i64 },
}

#[derive(Debug, Serialize, Deserialize)]
pub struct HoldingDto {
    pub asset_id: String,
    pub amount: Decimal,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct WalletSummaryDto {
    pub balance_usd: Decimal,
    pub holdings: Vec<HoldingDto>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct TransactionDto {
    pub id: String,
    pub asset_id: String,
    pub amount: Decimal,
    pub tx_type: String,
    pub created_at: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub enum ServerResponse {
    Message(String),
    Error(String),

    Offerings(Vec<Offering>),
    Price(Offering), // NEW

    WalletSummary(WalletSummaryDto),
    Transactions(Vec<TransactionDto>),
}