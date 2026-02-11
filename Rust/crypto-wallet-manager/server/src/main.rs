mod handler;
mod errors;
mod state;
mod db;
mod auth;
mod services;

use std::sync::{Arc, Mutex};
use dotenv::dotenv;
use std::env;
use tokio::net::TcpListener;

use state::AppState;
use db::user_repo;

use crate::services::coin_api::CoinApiService;

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    dotenv().ok();

    let api_key: String =
        env::var("COIN_API_KEY")
            .expect("API KEY missing");

    let listener: TcpListener = TcpListener::bind("127.0.0.1:8080").await?;
    println!("Server running on 127.0.0.1:8080");

    let users = user_repo::load_users();
    let coin_service = Arc::new(CoinApiService::new(api_key));
    let state = Arc::new(AppState::new(coin_service, users));

    loop {
        let (socket, addr) = listener.accept().await?;

        println!("Client connected: {}", addr);

        let shared_state = Arc::clone(&state);

        tokio::spawn(async move {
            if let Err(error) =
                handler::handle_client(socket, shared_state).await {

                println!("Connection error: {:?}", error);
            }
        });
    }
}