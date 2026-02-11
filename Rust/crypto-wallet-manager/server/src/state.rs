use std::collections::HashMap;
use std::sync::Arc;

use common::models::User;
use crate::services::coin_api::CoinApiService;

pub struct AppState {
    pub users: HashMap<String, User>,
    pub coin_service: Arc<CoinApiService>,
}

impl AppState {
    pub fn new(coin_service: Arc<CoinApiService>, users: HashMap<String, User>) -> Self {
        Self {
            users,
            coin_service,
        }
    }
}
