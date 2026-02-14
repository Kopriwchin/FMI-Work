use serde::{Serialize, Deserialize};
use rust_decimal::Decimal;

#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Offering {
    pub asset_id: String,
    pub price_usd: Decimal,
}
