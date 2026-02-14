mod handler;
mod errors;
mod state;
mod db;
mod auth;
mod services;

use std::sync::Arc;
use dotenv::dotenv;
use std::env;
use tokio::net::TcpListener;

use sqlx::sqlite::SqlitePool;
use crate::state::AppState;
use crate::db::init_db;
use crate::services::coin_api::CoinApiService;

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    dotenv().ok();

    let db: SqlitePool = init_db().await;

    let api_key: String =
        env::var("COIN_API_KEY").expect("COIN_API_KEY missing");

    let coin_service: Arc<CoinApiService> = Arc::new(CoinApiService::new(api_key));
    let state: Arc<AppState> = Arc::new(AppState::new(db, coin_service));

    let listener: TcpListener = TcpListener::bind("127.0.0.1:8080").await?;
    println!("Server running on 127.0.0.1:8080");

    loop {
        let (socket, addr) = listener.accept().await?;
        println!("Client connected: {}", addr);

        let shared_state: Arc<AppState> = Arc::clone(&state);

        tokio::spawn(async move {
            if let Err(error) = handler::handle_client(socket, shared_state).await {
                println!("Connection error: {:?}", error);
            }
        });
    }
}
