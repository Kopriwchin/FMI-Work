use std::sync::Arc;
use common::commands::{ClientCommand, ServerResponse};

use tokio::io::{AsyncBufReadExt, AsyncWriteExt, BufReader};
use tokio::net::TcpStream;

use crate::auth::service;
use crate::auth::session::Session;
use crate::state::AppState;

pub async fn handle_client(
    socket: TcpStream,
    state: Arc<AppState>,
) -> Result<(), Box<dyn std::error::Error>> {

    let (reader, mut writer) = socket.into_split();

    let mut buffered_reader: BufReader<_> = BufReader::new(reader);
    let mut message: String = String::new();

    let mut session: Session = Session::new();

    loop {

        message.clear();

        let bytes_read: usize =
            buffered_reader.read_line(&mut message).await?;

        if bytes_read == 0 {
            println!("Client disconnected");
            return Ok(());
        }

        let command: ClientCommand =
            serde_json::from_str(message.trim())?;

        let response: ServerResponse = match command {

            ClientCommand::Register { username, password } => {

                match service::register(&username, &password) {

                    Ok(_) => ServerResponse::Ok("User registered".to_string()),

                    Err(_) => ServerResponse::Error("Invalid credentials".to_string()),
                }
            }

            ClientCommand::Login { username, password } => {

                match service::login(&username, &password) {

                    Ok(user) => {

                        session.user_id = Some(user.id);

                        ServerResponse::Ok("Logged in".to_string())
                    }

                    Err(_) => ServerResponse::Error("Invalid credentials".to_string()),
                }
            }

            ClientCommand::GetProfile => {

                if !session.is_authenticated() {
                    ServerResponse::Error("Authentication required".to_string())
                } else {

                    let user_id: String =
                        session.user_id.clone().unwrap();

                    ServerResponse::Ok(format!("User id: {}", user_id))
                }
            }

            ClientCommand::ListOfferings => {

                match state.coin_service.get_assets().await {

                    Ok(assets) => {

                        let formatted: Vec<String> = assets
                            .iter()
                            .map(|a| {
                                format!(
                                    "{} - ${}",
                                    a.asset_id,
                                    a.price_usd.unwrap_or(0.0)
                                )
                            })
                            .collect();

                        ServerResponse::Ok(formatted.join("\n"))
                    }

                    Err(_) => ServerResponse::Error(
                        "Failed to fetch crypto data".to_string()
                    ),
                }
            }

            _ => ServerResponse::Error("Command not implemented".to_string()),
        };

        let response_json: String =
            serde_json::to_string(&response)?;

        writer.write_all(response_json.as_bytes()).await?;
        writer.write_all(b"\n").await?;
    }
}