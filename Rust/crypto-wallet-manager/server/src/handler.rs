use std::sync::{Arc, Mutex};

use common::commands::{ClientCommand, ServerResponse};
use common::models::User;

use tokio::io::{AsyncBufReadExt, AsyncWriteExt, BufReader};
use tokio::net::TcpStream;

use crate::state::AppState;
use crate::db::user_repo;

pub async fn handle_client(
    socket: TcpStream,
    state: Arc<Mutex<AppState>>,
) -> Result<(), Box<dyn std::error::Error>> {
    let (reader, mut writer) = socket.into_split();

    let mut buffered_reader: BufReader<_> = BufReader::new(reader);
    let mut message: String = String::new();

    loop {
        message.clear();

        let bytes_read: usize = buffered_reader.read_line(&mut message).await?;

        if bytes_read == 0 {
            println!("Client disconnected");
            return Ok(());
        }

        let command: ClientCommand = serde_json::from_str(message.trim())?;

        println!("Received command: {:?}", command);

        let response: ServerResponse = match command {
            ClientCommand::Register { username, password } => {
                let mut app_state = state.lock().unwrap();

                if app_state.users.contains_key(&username) {
                    ServerResponse::Error("User already exists".to_string())
                } else {
                    let user = User::new(username.clone(), password);

                    app_state.users.insert(username, user);

                    let _ = user_repo::save_users(&app_state.users);

                    ServerResponse::Ok("User registered successfully".to_string())
                }
            }

            _ => ServerResponse::Error("Command not implemented yet".to_string()),
        };

        let response_json: String = serde_json::to_string(&response)?;

        writer.write_all(response_json.as_bytes()).await?;
        writer.write_all(b"\n").await?;
    }
}