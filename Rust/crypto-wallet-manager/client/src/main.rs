use common::commands::{ClientCommand, ServerResponse};
use rust_decimal::Decimal;
use std::io::{self, Write};
use std::str::FromStr;

use crate::network::TcpClient;

mod network;

fn print_help() {
    println!(
        r#"
Available commands:
  help
  register <username> <password>
  login <username> <password>
  offerings
  price <asset_id>             (real-time from CoinAPI)
  deposit <amount_usd>
  buy <asset_id> <amount_usd>
  sell <asset_id>              (sell all of this asset)
  wallet
  portfolio
  tx <page> <page_size>
  exit

Examples:
  register alice pass123
  login alice pass123
  offerings
  price BTC
  deposit 1000
  buy BTC 200
  wallet
  tx 1 20
"#
    );
}


fn require_login(logged_in_user_id: &Option<String>) -> bool {
    if logged_in_user_id.is_none() {
        println!("You must login first.");
        return false;
    }
    true
}

fn parse_decimal(input: &str) -> Result<Decimal, String> {
    Decimal::from_str(input).map_err(|_| "Invalid number".to_string())
}

fn prompt(prefix: &str) -> io::Result<String> {
    print!("{}", prefix);
    io::stdout().flush()?;

    let mut line: String = String::new();
    io::stdin().read_line(&mut line)?;
    Ok(line.trim().to_string())
}

fn format_response(resp: &ServerResponse) {
    match resp {
        ServerResponse::Message(msg) => println!("{}", msg),
        ServerResponse::Error(msg) => println!("Error: {}", msg),

        ServerResponse::Offerings(list) => {
            if list.is_empty() {
                println!("No offerings.");
                return;
            }
            for o in list {
                println!("{} - ${}", o.asset_id, o.price_usd);
            }
        }

        ServerResponse::Price(p) => {
            println!("{} - ${}", p.asset_id, p.price_usd);
        }

        ServerResponse::WalletSummary(summary) => {
            println!("Balance (USD): {}", summary.balance_usd);

            if summary.holdings.is_empty() {
                println!("Holdings: (none)");
                return;
            }

            println!("Holdings:");
            for h in &summary.holdings {
                println!("  {}: {}", h.asset_id, h.amount);
            }
        }

        ServerResponse::Transactions(list) => {
            if list.is_empty() {
                println!("No transactions.");
                return;
            }

            for t in list {
                println!(
                    "{} | {} | {} | {} | {}",
                    t.created_at, t.tx_type, t.asset_id, t.amount, t.id
                );
            }
        }
    }
}


fn build_command(
    input: &str,
    logged_in: &Option<String>,
) -> Result<Option<ClientCommand>, String> {
    let parts: Vec<&str> = input.split_whitespace().collect();
    if parts.is_empty() {
        return Ok(None);
    }

    let cmd_string: String = parts[0].to_lowercase();
    let cmd: &str = cmd_string.as_str();

    match cmd {
        "help" => Ok(None),

        "exit" | "quit" => Ok(Some(ClientCommand::GetProfile)),

        "register" => {
            if parts.len() != 3 {
                return Err("Usage: register <username> <password>".to_string());
            }
            Ok(Some(ClientCommand::Register {
                username: parts[1].to_string(),
                password: parts[2].to_string(),
            }))
        }

        "login" => {
            if parts.len() != 3 {
                return Err("Usage: login <username> <password>".to_string());
            }
            Ok(Some(ClientCommand::Login {
                username: parts[1].to_string(),
                password: parts[2].to_string(),
            }))
        }

        "price" => {
            if parts.len() != 2 {
                return Err("Usage: price <asset_id>".to_string());
            }
            Ok(Some(ClientCommand::GetPrice {
                asset_id: parts[1].to_string(),
            }))
        }

        "offerings" => Ok(Some(ClientCommand::ListOfferings)),

        "deposit" => {
            if !require_login(logged_in) {
                return Ok(None);
            }
            if parts.len() != 2 {
                return Err("Usage: deposit <amount_usd>".to_string());
            }
            let amount: Decimal = parse_decimal(parts[1])?;
            Ok(Some(ClientCommand::Deposit { amount }))
        }

        "buy" => {
            if !require_login(logged_in) {
                return Ok(None);
            }
            if parts.len() != 3 {
                return Err("Usage: buy <asset_id> <amount_usd>".to_string());
            }
            let asset_id: String = parts[1].to_string();
            let amount: Decimal = parse_decimal(parts[2])?;
            Ok(Some(ClientCommand::Buy { asset_id, amount }))
        }

        "sell" => {
            if !require_login(logged_in) {
                return Ok(None);
            }
            if parts.len() != 2 {
                return Err("Usage: sell <asset_id>".to_string());
            }
            Ok(Some(ClientCommand::Sell {
                asset_id: parts[1].to_string(),
            }))
        }

        "wallet" => {
            if !require_login(logged_in) {
                return Ok(None);
            }
            Ok(Some(ClientCommand::GetWalletSummary))
        }

        "portfolio" => {
            if !require_login(logged_in) {
                return Ok(None);
            }
            Ok(Some(ClientCommand::GetWalletOverallSummary))
        }

        "tx" => {
            if !require_login(logged_in) {
                return Ok(None);
            }
            if parts.len() != 3 {
                return Err("Usage: tx <page> <page_size>".to_string());
            }

            let page: i64 = parts[1].parse::<i64>().map_err(|_| "Invalid page".to_string())?;
            let page_size: i64 =
                parts[2].parse::<i64>().map_err(|_| "Invalid page_size".to_string())?;

            Ok(Some(ClientCommand::GetTransactionHistory { page, page_size }))
        }

        _ => Err("Unknown command. Type: help".to_string()),
    }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {

    let mut client: TcpClient = TcpClient::connect("127.0.0.1:8080").await?;

    let mut logged_in_user_id: Option<String> = None;
    let mut logged_in_username: Option<String> = None;
    let mut prompt_prefix: String = "wallet> ".to_string();

    print_help();

    loop {
        let input: String = prompt(&prompt_prefix)?;
        if input.is_empty() {
            continue;
        }

        let first: String = input.split_whitespace().next().unwrap().to_lowercase();
        if first == "help" {
            print_help();
            continue;
        }
        if first == "exit" || first == "quit" {
            break;
        }

        let cmd_opt: Option<ClientCommand> = match build_command(&input, &logged_in_user_id) {
            Ok(v) => v,
            Err(e) => {
                println!("{}", e);
                continue;
            }
        };

        let cmd: ClientCommand = match cmd_opt {
            Some(c) => c,
            None => continue,
        };

        let resp: ServerResponse = client.send(cmd).await?;
        format_response(&resp);

        match &resp {
            ServerResponse::Message(msg) => {
                if msg.to_lowercase().contains("logged in") {
                    let parts: Vec<&str> = input.split_whitespace().collect();
                    if parts.len() >= 2 {
                        let username: String = parts[1].to_string();

                        logged_in_user_id = Some("ok".to_string());
                        logged_in_username = Some(username.clone());
                        prompt_prefix = format!("wallet({})> ", username);
                    }
                }
            }
            _ => {}
        }
    }

    Ok(())
}
