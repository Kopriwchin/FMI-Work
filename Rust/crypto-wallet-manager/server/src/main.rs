use std::io::{self, Write};

use common::commands::{ClientCommand, ServerResponse};

mod network;

fn print_help() {
    println!(
        r#"
Available commands:
  help
  register <username> <password>
  login <username> <password>

  deposit <amount_usd>
  list | list-offerings
  buy <ASSET_ID> <usd_amount>
  sell <ASSET_ID>

  wallet
  overall
  history <page> <page_size>

  quit | exit
"#
    );
}

fn parse_command(line: &str) -> Result<Option<ClientCommand>, String> {
    let trimmed: &str = line.trim();
    if trimmed.is_empty() {
        return Ok(None);
    }

    let parts: Vec<&str> = trimmed.split_whitespace().collect();
    let cmd: String = parts[0].to_lowercase();

    match cmd.as_str() {
        "help" => Ok(None),

        "quit" | "exit" => Ok(Some(ClientCommand::GetProfile)),

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

        "deposit" => {
            if parts.len() != 2 {
                return Err("Usage: deposit <amount_usd>".to_string());
            }
            let amount = parts[1]
                .parse()
                .map_err(|_| "Invalid amount".to_string())?;
            Ok(Some(ClientCommand::Deposit { amount }))
        }

        "list" | "list-offerings" => Ok(Some(ClientCommand::ListOfferings)),

        "buy" => {
            if parts.len() != 3 {
                return Err("Usage: buy <ASSET_ID> <usd_amount>".to_string());
            }
            let asset_id: String = parts[1].to_string();
            let amount = parts[2]
                .parse()
                .map_err(|_| "Invalid usd_amount".to_string())?;
            Ok(Some(ClientCommand::Buy { asset_id, amount }))
        }

        "sell" => {
            if parts.len() != 2 {
                return Err("Usage: sell <ASSET_ID>".to_string());
            }
            Ok(Some(ClientCommand::Sell {
                asset_id: parts[1].to_string(),
            }))
        }

        "wallet" => Ok(Some(ClientCommand::GetWalletSummary)),

        "overall" => Ok(Some(ClientCommand::GetWalletOverallSummary)),

        "history" => {
            if parts.len() != 3 {
                return Err("Usage: history <page> <page_size>".to_string());
            }
            let page: i64 = parts[1].parse().map_err(|_| "Invalid page".to_string())?;
            let page_size: i64 = parts[2]
                .parse()
                .map_err(|_| "Invalid page_size".to_string())?;

            Ok(Some(ClientCommand::GetTransactionHistory { page, page_size }))
        }

        _ => Err("Unknown command. Type 'help'.".to_string()),
    }
}

fn print_response(resp: ServerResponse) {
    match resp {
        ServerResponse::Message(text) => {
            println!("{}", text);
        }

        ServerResponse::Error(text) => {
            println!("Error: {}", text);
        }

        ServerResponse::Offerings(list) => {
            if list.is_empty() {
                println!("No offerings.");
                return;
            }

            println!("Offerings (showing {}):", list.len());
            for o in list {
                println!("  {:<8} ${}", o.asset_id, o.price_usd);
            }
        }

        ServerResponse::WalletSummary(summary) => {
            println!("Balance (USD): {}", summary.balance_usd);
            if summary.holdings.is_empty() {
                println!("Holdings: (none)");
            } else {
                println!("Holdings:");
                for h in summary.holdings {
                    println!("  {:<8} {}", h.asset_id, h.amount);
                }
            }
        }

        ServerResponse::Transactions(list) => {
            if list.is_empty() {
                println!("No transactions.");
                return;
            }

            println!("Transactions ({}):", list.len());
            for t in list {
                println!(
                    "  {}  {:<4}  {:<8} {}",
                    t.created_at, t.tx_type, t.asset_id, t.amount
                );
            }
        }
    }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut is_logged_in: bool = false;
    let mut current_user: Option<String> = None;

    let mut client = network::TcpJsonClient::connect("127.0.0.1:8080").await?;

    println!("Crypto Wallet Manager client. Type 'help'.");

    loop {
        match &current_user {
            Some(username) => print!("{} > ", username),
            None => print!("guest > "),
        }
        io::stdout().flush()?;

        let mut line: String = String::new();
        io::stdin().read_line(&mut line)?;

        let trimmed = line.trim();
        if trimmed.eq_ignore_ascii_case("help") {
            print_help();
            continue;
        }

        if trimmed.eq_ignore_ascii_case("quit") || trimmed.eq_ignore_ascii_case("exit") {
            break;
        }

        let cmd_opt = match parse_command(&line) {
            Ok(v) => v,
            Err(e) => {
                println!("Error: {}", e);
                continue;
            }
        };

        let Some(cmd) = cmd_opt else { continue };

        // Block protected commands locally
        match &cmd {
            ClientCommand::Buy { .. }
            | ClientCommand::Sell { .. }
            | ClientCommand::Deposit { .. }
            | ClientCommand::GetWalletSummary
            | ClientCommand::GetWalletOverallSummary
            | ClientCommand::GetTransactionHistory { .. } => {
                if !is_logged_in {
                    println!("Error: You must login first.");
                    continue;
                }
            }
            _ => {}
        }

        let resp: ServerResponse = client.send(cmd.clone()).await?;
        match (&cmd, &resp) {
            (ClientCommand::Login { username, .. }, ServerResponse::Message(msg))
            if msg.contains("Logged in") =>
                {
                    is_logged_in = true;
                    current_user = Some(username.clone());
                }
            _ => {}
        }

        match (&cmd, &resp) {
            (ClientCommand::Login { .. }, ServerResponse::Message(msg))
            if msg.contains("Logged in") =>
                {
                    is_logged_in = true;
                }
            _ => {}
        }

        print_response(resp);

    }

    Ok(())
}
