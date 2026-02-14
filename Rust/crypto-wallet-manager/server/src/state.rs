use crate::services::coin_api::CoinApi;
use std::sync::Arc;
use sqlx::SqlitePool;

pub struct AppState {
    pub db: SqlitePool,
    pub coin_service: Arc<dyn CoinApi>,
}

impl AppState {
    pub fn new(db: SqlitePool, coin_service: Arc<dyn CoinApi>) -> Self {
        Self { db, coin_service }
    }
}
