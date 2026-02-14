use crate::db::user_repo;
use crate::services::wallet;

use std::sync::Arc;
use rust_decimal::Decimal;
use common::commands::{ClientCommand, ServerResponse};

use tokio::io::{AsyncBufReadExt, AsyncWriteExt, BufReader};
use tokio::net::TcpStream;
use common::models::offering::Offering;
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

        let command: ClientCommand = serde_json::from_str(message.trim())?;

        let response: ServerResponse = match command {
            ClientCommand::Register { username, password } => {
                match service::register(&state, &username, &password).await
                {
                    Ok(_) =>
                        ServerResponse::Message("User registered".into()),
                    Err(_) =>
                        ServerResponse::Error("Invalid credentials".into()),
                }
            }

            ClientCommand::Login { username, password } => {
                match service::login(&state, &username, &password).await
                {
                    Ok(user) => {
                        session.user_id = Some(user.id);
                        ServerResponse::Message("Logged in".into())
                    }
                    Err(_) =>
                        ServerResponse::Error("Invalid credentials".into()),
                }
            }

            ClientCommand::GetProfile => {
                if !session.is_authenticated() {
                    ServerResponse::Error("Authentication required".to_string())
                } else {

                    let user_id: String = session.user_id.clone().unwrap();

                    ServerResponse::Message(format!("User id: {}", user_id))
                }
            }

            ClientCommand::ListOfferings => {
                match state.coin_service.get_assets().await {
                    Ok(assets) => {
                        let offerings: Vec<Offering> = assets
                            .iter()
                            .map(|a| Offering {
                                asset_id: a.asset_id.clone(),
                                price_usd: Decimal::try_from(a.price_usd.unwrap_or(0.0)).unwrap(),
                            })
                            .collect();

                        ServerResponse::Offerings(offerings)
                    }

                    Err(_) => ServerResponse::Error(
                        "Failed to fetch crypto data".to_string()
                    ),
                }
            }

            ClientCommand::Deposit { amount } => {
                let balance_string = user.wallet.balance.to_string();

                sqlx::query!(
                        "INSERT INTO wallets (user_id, balance)
                         VALUES (?1, ?2)",
                    user.id,
                    balance_string
                    .execute(db)
                    .await?;


                let user = session
                    .user_mut(&mut users)
                    .ok_or("Not authenticated")?;

                wallet::deposit(user, amount);

                user_repo::save_users(&users).ok();

                ServerResponse::Message("Deposit successful".into())
            }



            _ => ServerResponse::Error("Command not implemented".to_string()),
        };

        let response_json: String = serde_json::to_string(&response)?;

        writer.write_all(response_json.as_bytes()).await?;
        writer.write_all(b"\n").await?;
    }
}