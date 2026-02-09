mod handler;
mod state;
mod db;

use std::sync::{Arc, Mutex};

use tokio::net::TcpListener;

use state::AppState;
use db::user_repo;


#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {

    let listener: TcpListener = TcpListener::bind("127.0.0.1:8080").await?;

    println!("Server running on 127.0.0.1:8080");
    let users = user_repo::load_users();

    let state: Arc<Mutex<AppState>> =
        Arc::new(Mutex::new(AppState { users }));

    loop {
        let (socket, addr) = listener.accept().await?;

        println!("Client connected: {}", addr);

        let shared_state = Arc::clone(&state);

        tokio::spawn(async move {
            if let Err(error) = handler::handle_client(socket, shared_state).await {
                println!("Connection error: {:?}", error);
            }
        });
    }
}
