use sqlx::sqlite::SqlitePool;

pub struct AuthUser {
    pub id: String,
    pub username: String,
    pub password_hash: String,
}

pub async fn create_user(
    db: &SqlitePool,
    id: &str,
    username: &str,
    password_hash: &str,
) -> Result<(), sqlx::Error> {

    sqlx::query!(
        "INSERT INTO users (id, username, password_hash)
         VALUES (?1, ?2, ?3)",
        id,
        username,
        password_hash
    )
        .execute(db)
        .await?;

    sqlx::query!(
        "INSERT INTO wallets (user_id, balance)
         VALUES (?1, '0')",
        id
    )
        .execute(db)
        .await?;

    Ok(())
}

pub async fn find_by_username(
    db: &SqlitePool,
    username: &str,
) -> Result<Option<AuthUser>, sqlx::Error> {

    let record = sqlx::query!(
        "SELECT id, username, password_hash
         FROM users
         WHERE username = ?1",
        username
    )
        .fetch_optional(db)
        .await?;

    Ok(record.map(|r| AuthUser {
        id: r.id,
        username: r.username,
        password_hash: r.password_hash,
    }))
}
