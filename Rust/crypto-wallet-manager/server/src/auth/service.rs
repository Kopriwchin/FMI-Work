use crate::auth::password::{hash_password, verify_password};
use crate::db::user_repo;
use crate::errors::AuthError;
use crate::state::AppState;
use uuid::Uuid;

pub async fn register(
    state: &AppState,
    username: &str,
    password: &str,
) -> Result<(), AuthError> {

    let existing = user_repo::find_by_username(&state.db, username)
        .await
        .map_err(|_| AuthError::InvalidCredentials)?;

    if existing.is_some() {
        return Err(AuthError::InvalidCredentials);
    }

    let hashed: String = hash_password(password)
        .map_err(|_| AuthError::InvalidCredentials)?;

    let id: String = Uuid::new_v4().to_string();

    user_repo::create_user(&state.db, &id, username, &hashed)
        .await
        .map_err(|_| AuthError::InvalidCredentials)?;

    Ok(())
}

pub async fn login(
    state: &AppState,
    username: &str,
    password: &str,
) -> Result<user_repo::AuthUser, AuthError> {

    let user = user_repo::find_by_username(&state.db, username)
        .await
        .map_err(|_| AuthError::InvalidCredentials)?
        .ok_or(AuthError::InvalidCredentials)?;

    if !verify_password(&user.password_hash, password) {
        return Err(AuthError::InvalidCredentials);
    }

    Ok(user)
}
