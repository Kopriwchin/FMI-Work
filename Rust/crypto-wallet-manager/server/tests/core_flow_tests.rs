use std::env;
use std::sync::Arc;

use rust_decimal::Decimal;
use sqlx::sqlite::SqlitePoolOptions;
use sqlx::SqlitePool;
use uuid::Uuid;

use server::auth;
use server::services::{cache, trading};
use server::services::coin_api::CoinApiService;
use server::state::AppState;

async fn setup_db() -> SqlitePool {
    // IMPORTANT:
    // sqlite::memory: is per-connection. Keep max_connections=1 so all queries see the same DB.
    let db: SqlitePool = SqlitePoolOptions::new()
        .max_connections(1)
        .connect("sqlite::memory:")
        .await
        .unwrap();

    sqlx::query(
        r#"
        PRAGMA foreign_keys = ON;
        "#,
    )
        .execute(&db)
        .await
        .unwrap();

    sqlx::query(
        r#"
        CREATE TABLE IF NOT EXISTS users (
            id TEXT PRIMARY KEY,
            username TEXT NOT NULL UNIQUE,
            password_hash TEXT NOT NULL
        );
        "#,
    )
        .execute(&db)
        .await
        .unwrap();

    sqlx::query(
        r#"
        CREATE TABLE IF NOT EXISTS wallets (
            user_id TEXT PRIMARY KEY,
            balance TEXT NOT NULL,
            FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE
        );
        "#,
    )
        .execute(&db)
        .await
        .unwrap();

    sqlx::query(
        r#"
        CREATE TABLE IF NOT EXISTS holdings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id TEXT NOT NULL,
            asset_id TEXT NOT NULL,
            amount TEXT NOT NULL,
            FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE
        );
        "#,
    )
        .execute(&db)
        .await
        .unwrap();

    sqlx::query(
        r#"
        CREATE TABLE IF NOT EXISTS transactions (
            id TEXT PRIMARY KEY,
            user_id TEXT NOT NULL,
            asset_id TEXT NOT NULL,
            amount TEXT NOT NULL,
            type TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE
        );
        "#,
    )
        .execute(&db)
        .await
        .unwrap();

    sqlx::query(
        r#"
        CREATE TABLE IF NOT EXISTS cached_assets (
            asset_id TEXT PRIMARY KEY,
            name TEXT,
            price_usd TEXT,
            last_updated INTEGER
        );
        "#,
    )
        .execute(&db)
        .await
        .unwrap();

    db
}

fn build_state(db: SqlitePool) -> Arc<AppState> {
    let api_key: String = env::var("COIN_API_KEY").unwrap_or_else(|_| "DUMMY".to_string());
    let coin_service: Arc<CoinApiService> = Arc::new(CoinApiService::new(api_key));
    Arc::new(AppState::new(db, coin_service))
}

async fn insert_user_and_wallet(
    db: &SqlitePool,
    user_id: &str,
    username: &str,
    password_hash: &str,
    balance: &str,
) {
    sqlx::query(
        r#"
        INSERT INTO users (id, username, password_hash)
        VALUES (?1, ?2, ?3)
        "#,
    )
        .bind(user_id)
        .bind(username)
        .bind(password_hash)
        .execute(db)
        .await
        .unwrap();

    sqlx::query(
        r#"
        INSERT INTO wallets (user_id, balance)
        VALUES (?1, ?2)
        "#,
    )
        .bind(user_id)
        .bind(balance)
        .execute(db)
        .await
        .unwrap();
}

#[tokio::test]
async fn register_and_login_success() {
    let db: SqlitePool = setup_db().await;
    let state: Arc<AppState> = build_state(db);

    auth::service::register(&state, "alice", "pass123")
        .await
        .expect("register should succeed");

    let user = auth::service::login(&state, "alice", "pass123")
        .await
        .expect("login should succeed");

    assert_eq!(user.username, "alice");
    assert!(!user.id.is_empty());
}

#[tokio::test]
async fn register_duplicate_fails() {
    let db: SqlitePool = setup_db().await;
    let state: Arc<AppState> = build_state(db);

    auth::service::register(&state, "bob", "p1").await.unwrap();
    let second = auth::service::register(&state, "bob", "p2").await;

    assert!(second.is_err(), "duplicate username should fail");
}

#[tokio::test]
async fn login_wrong_password_fails() {
    let db: SqlitePool = setup_db().await;
    let state: Arc<AppState> = build_state(db);

    auth::service::register(&state, "carol", "correct").await.unwrap();
    let res = auth::service::login(&state, "carol", "wrong").await;

    assert!(res.is_err(), "wrong password should fail");
}

#[tokio::test]
async fn deposit_and_wallet_summary() {
    let db: SqlitePool = setup_db().await;
    let state: Arc<AppState> = build_state(db);

    // Register creates user + wallet(balance 0)
    auth::service::register(&state, "dave", "p").await.unwrap();
    let user = auth::service::login(&state, "dave", "p").await.unwrap();

    trading::deposit(&state, &user.id, Decimal::from(100))
        .await
        .expect("deposit should succeed");

    let summary = trading::wallet_summary(&state, &user.id)
        .await
        .expect("wallet_summary should succeed");

    assert_eq!(summary.balance_usd, Decimal::from(100));
    assert_eq!(summary.holdings.len(), 0);
}

#[tokio::test]
async fn transaction_history_pagination_orders_desc() {
    let db: SqlitePool = setup_db().await;

    // Create a user directly (no hashing dependency for this test)
    let user_id: String = Uuid::new_v4().to_string();
    insert_user_and_wallet(&db, &user_id, "eve", "hash", "0").await;

    // Insert 3 transactions (created_at uses CURRENT_TIMESTAMP; ordering by created_at DESC)
    // To make ordering deterministic, we insert with small delays OR just rely on insertion order.
    // SQLite timestamp resolution is usually 1 second; so we set created_at explicitly.
    sqlx::query(
        r#"
        INSERT INTO transactions (id, user_id, asset_id, amount, type, created_at)
        VALUES (?1, ?2, ?3, ?4, ?5, ?6)
        "#,
    )
        .bind("t1")
        .bind(&user_id)
        .bind("BTC")
        .bind("0.1")
        .bind("BUY")
        .bind("2026-01-01 00:00:01")
        .execute(&db)
        .await
        .unwrap();

    sqlx::query(
        r#"
        INSERT INTO transactions (id, user_id, asset_id, amount, type, created_at)
        VALUES (?1, ?2, ?3, ?4, ?5, ?6)
        "#,
    )
        .bind("t2")
        .bind(&user_id)
        .bind("ETH")
        .bind("0.2")
        .bind("BUY")
        .bind("2026-01-01 00:00:02")
        .execute(&db)
        .await
        .unwrap();

    sqlx::query(
        r#"
        INSERT INTO transactions (id, user_id, asset_id, amount, type, created_at)
        VALUES (?1, ?2, ?3, ?4, ?5, ?6)
        "#,
    )
        .bind("t3")
        .bind(&user_id)
        .bind("BTC")
        .bind("0.05")
        .bind("SELL")
        .bind("2026-01-01 00:00:03")
        .execute(&db)
        .await
        .unwrap();

    let state: Arc<AppState> = build_state(db);

    let page1 = trading::transaction_history(&state, &user_id, 1, 2)
        .await
        .expect("page1 should succeed");

    assert_eq!(page1.len(), 2);
    assert_eq!(page1[0].id, "t3");
    assert_eq!(page1[1].id, "t2");

    let page2 = trading::transaction_history(&state, &user_id, 2, 2)
        .await
        .expect("page2 should succeed");

    assert_eq!(page2.len(), 1);
    assert_eq!(page2[0].id, "t1");
}

#[tokio::test]
async fn cache_returns_rows_from_db_without_refresh_when_fresh() {
    let db: SqlitePool = setup_db().await;
    let state: Arc<AppState> = build_state(db);

    // Seed cache with a "fresh" timestamp based on the real system time
    let now: i64 = std::time::SystemTime::now()
        .duration_since(std::time::UNIX_EPOCH)
        .unwrap()
        .as_secs() as i64;

    sqlx::query("DELETE FROM cached_assets")
        .execute(&state.db)
        .await
        .unwrap();

    sqlx::query(
        r#"
        INSERT INTO cached_assets (asset_id, name, price_usd, last_updated)
        VALUES (?1, ?2, ?3, ?4)
        "#,
    )
        .bind("BTC")
        .bind("Bitcoin")
        .bind("70000.0")
        .bind(now)
        .execute(&state.db)
        .await
        .unwrap();

    let assets = cache::get_cached_assets(&state)
        .await
        .expect("cache read should succeed");

    assert!(!assets.is_empty());
    assert_eq!(assets[0].0, "BTC");
    assert_eq!(assets[0].1, "Bitcoin");
}

#[tokio::test]
async fn optional_buy_and_sell_all_live_coinapi() {
    // This test hits CoinAPI via get_asset(). Run only if you have COIN_API_KEY set.
    if env::var("COIN_API_KEY").is_err() {
        eprintln!("Skipping live CoinAPI test (COIN_API_KEY not set).");
        return;
    }

    let db: SqlitePool = setup_db().await;
    let state: Arc<AppState> = build_state(db);

    auth::service::register(&state, "live", "p").await.unwrap();
    let user = auth::service::login(&state, "live", "p").await.unwrap();

    // Deposit enough USD.
    trading::deposit(&state, &user.id, Decimal::from(1000))
        .await
        .unwrap();

    // Buy BTC for $100 (amount = USD spend in your handler)
    trading::buy(&state, &user.id, "BTC", Decimal::from(100))
        .await
        .unwrap();

    let after_buy = trading::wallet_summary(&state, &user.id).await.unwrap();
    assert!(after_buy.balance_usd < Decimal::from(1000));
    assert!(
        after_buy.holdings.iter().any(|h| h.asset_id == "BTC"),
        "should have BTC holding after buy"
    );

    // Sell all BTC
    trading::sell_all(&state, &user.id, "BTC").await.unwrap();

    let after_sell = trading::wallet_summary(&state, &user.id).await.unwrap();
    assert!(
        after_sell.holdings.iter().all(|h| h.asset_id != "BTC"),
        "BTC holding should be removed after sell_all"
    );

    let history = trading::transaction_history(&state, &user.id, 1, 50)
        .await
        .unwrap();

    assert!(
        history.iter().any(|t| t.tx_type == "BUY"),
        "history should contain BUY"
    );
    assert!(
        history.iter().any(|t| t.tx_type == "SELL"),
        "history should contain SELL"
    );
}
