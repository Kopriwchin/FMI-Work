use std::sync::{Arc};
use sqlx::SqlitePool;
use crate::services::coin_api::CoinApiService;

pub struct AppState {
    pub db: SqlitePool,
    pub coin_service: Arc<CoinApiService>,
}

impl AppState {
    pub fn new(
        db: SqlitePool,
        coin_service: Arc<CoinApiService>,
    ) -> Self {
        Self { db, coin_service }
    }
}