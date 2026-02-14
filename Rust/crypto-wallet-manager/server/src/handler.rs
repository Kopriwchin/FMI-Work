use std::str::FromStr;
use std::sync::Arc;
use common::commands::{ClientCommand, ServerResponse};

use tokio::io::{AsyncBufReadExt, AsyncWriteExt, BufReader};
use tokio::net::TcpStream;
use common::models::offering::Offering;
use crate::services::{cache, trading};
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
                match service::login(&state, &username, &password).await {
                    Ok(user) => {
                        session.user_id = Some(user.id);
                        ServerResponse::Message("Logged in".into())
                    }
                    Err(_) => ServerResponse::Error("Invalid credentials".into()),
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
                match cache::get_cached_assets(&state).await {

                    Ok(assets) => {

                        let offerings: Vec<Offering> = assets
                            .into_iter()
                            .map(|(asset_id, _name, price)| Offering {
                                asset_id,
                                price_usd: price,
                            })
                            .collect();

                        ServerResponse::Offerings(offerings)
                    }

                    Err(e) => ServerResponse::Error(e),
                }
            }

            ClientCommand::GetWalletSummary => {
                if !session.is_authenticated() {
                    ServerResponse::Error("Authentication required".into())
                } else {
                    let user_id: String = session.user_id.clone().unwrap();

                    match trading::wallet_summary(&state, &user_id).await {
                        Ok(summary) => ServerResponse::WalletSummary(summary),
                        Err(e) => ServerResponse::Error(e),
                    }
                }
            }

            ClientCommand::Deposit { amount } => {
                if !session.is_authenticated() {
                    ServerResponse::Error("Authentication required".into())
                } else {
                    let user_id: String = session.user_id.clone().unwrap();

                    match trading::deposit(&state, &user_id, amount).await {
                        Ok(_) => ServerResponse::Message("Deposit successful".into()),
                        Err(e) => ServerResponse::Error(e),
                    }
                }
            }

            ClientCommand::Buy { asset_id, amount } => {
                if !session.is_authenticated() {
                    ServerResponse::Error("Authentication required".into())
                } else {
                    let user_id: String = session.user_id.clone().unwrap();

                    match trading::buy(&state, &user_id, &asset_id, amount).await {
                        Ok(_) => ServerResponse::Message("Buy successful".into()),
                        Err(e) => ServerResponse::Error(e),
                    }
                }
            }

            ClientCommand::Sell { asset_id } => {
                if !session.is_authenticated() {
                    ServerResponse::Error("Authentication required".into())
                } else {
                    let user_id: String = session.user_id.clone().unwrap();

                    match trading::sell_all(&state, &user_id, &asset_id).await {
                        Ok(_) => ServerResponse::Message("Sell successful".into()),
                        Err(e) => ServerResponse::Error(e),
                    }
                }
            }

            ClientCommand::GetWalletOverallSummary => {
                if !session.is_authenticated() {
                    ServerResponse::Error("Authentication required".into())
                } else {
                    let user_id: String = session.user_id.clone().unwrap();

                    match trading::portfolio_value(&state, &user_id).await {
                        Ok(total) => ServerResponse::Message(format!("Total portfolio value (USD): {}", total)),
                        Err(e) => ServerResponse::Error(e),
                    }
                }
            }

            ClientCommand::GetTransactionHistory { page, page_size } => {
                if !session.is_authenticated() {
                    ServerResponse::Error("Authentication required".into())
                } else {
                    let user_id: String = session.user_id.clone().unwrap();

                    match trading::transaction_history(&state, &user_id, page, page_size).await {
                        Ok(list) => ServerResponse::Transactions(list),
                        Err(e) => ServerResponse::Error(e),
                    }
                }
            }

            ClientCommand::GetPrice { asset_id } => {
                match state.coin_service.get_asset(&asset_id).await {
                    Ok(asset) => {
                        if asset.type_is_crypto != Some(1) {
                            ServerResponse::Error("Not a crypto asset".into())
                        } else {
                            match asset.price_usd {
                                Some(price_f64) => {
                                    let price =
                                        rust_decimal::Decimal::from_str(&price_f64.to_string())
                                            .map_err(|_| "Invalid price format")?;

                                    ServerResponse::Price(Offering {
                                        asset_id: asset.asset_id,
                                        price_usd: price,
                                    })
                                }
                                None => ServerResponse::Error("No price available".into()),
                            }
                        }
                    }
                    Err(_) => ServerResponse::Error("Failed to fetch price".into()),
                }
            }
        };

        let response_json: String = serde_json::to_string(&response)?;

        writer.write_all(response_json.as_bytes()).await?;
        writer.write_all(b"\n").await?;
    }
}