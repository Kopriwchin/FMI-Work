use std::collections::HashMap;
use common::models::User;

pub struct AppState {
    pub users: HashMap<String, User>,
}

impl AppState {
    pub fn new() -> Self {
        Self {
            users: HashMap::new(),
        }
    }
}