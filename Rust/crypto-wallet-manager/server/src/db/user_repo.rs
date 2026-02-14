use std::collections::HashMap;
use std::fs;

use sqlx::sqlite::SqlitePool;
use common::models::user::User;

const USERS_FILE: &str = "users.json";

pub fn load_users() -> HashMap<String, User> {

    if let Ok(content) = fs::read_to_string(USERS_FILE) {

        if let Ok(users) = serde_json::from_str::<HashMap<String, User>>(&content) {
            return users;
        }
    }

    HashMap::new()
}

pub fn save_users(users: &HashMap<String, User>) -> Result<(), std::io::Error> {

    let json: String = serde_json::to_string_pretty(users)?;
    fs::write(USERS_FILE, json)?;

    Ok(())
}

pub async fn create_user(
    db: &SqlitePool,
    user: &User,
) -> Result<(), sqlx::Error> {

    sqlx::query!(
        "INSERT INTO users (id, username, password_hash)
         VALUES (?1, ?2, ?3)",
        user.id,
        user.username,
        user.password_hash
    )
        .execute(db)
        .await?;

    sqlx::query!(
        "INSERT INTO wallets (user_id, balance)
         VALUES (?1, ?2)",
        user.id,
        user.wallet.balance.to_string()
    )
        .execute(db)
        .await?;

    Ok(())
}

pub async fn find_by_username(
    db: &SqlitePool,
    username: &str,
) -> Result<Option<User>, sqlx::Error> {

    let record = sqlx::query!(
        "SELECT id, username, password_hash
         FROM users
         WHERE username = ?1",
        username
    )
        .fetch_optional(db)
        .await?;

    if let Some(r) = record {

        let wallet = sqlx::query!(
            "SELECT balance FROM wallets WHERE user_id = ?1",
            r.id
        )
            .fetch_one(db)
            .await?;

        let balance =
            rust_decimal::Decimal::from_str_exact(
                &wallet.balance
            ).unwrap();

        Ok(Some(User {
            id: r.id.unwrap(),
            username: r.username,
            password_hash: r.password_hash,
            wallet: common::models::wallet::Wallet {
                balance,
                assets: std::collections::HashMap::new(),
                transactions: Vec::new(),
            },
        }))
    } else {
        Ok(None)
    }
}