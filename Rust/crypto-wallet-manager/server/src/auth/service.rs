use crate::auth::password::{hash_password, verify_password};
use crate::errors::AuthError;
use crate::state::AppState;

use common::models::user::User;
use crate::db::user_repo;

pub async fn register(
    state: &AppState,
    username: &str,
    password: &str,
) -> Result<(), AuthError> {

    if user_repo::find_by_username(&state.db, username)
        .await
        .map_err(|_| AuthError::InvalidCredentials)?
        .is_some()
    {
        return Err(AuthError::InvalidCredentials);
    }

    let hashed =
        hash_password(password)
            .map_err(|_| AuthError::InvalidCredentials)?;

    let user =
        User::new(username.to_string(), hashed);

    user_repo::create_user(&state.db, &user)
        .await
        .map_err(|_| AuthError::InvalidCredentials)?;

    Ok(())
}

pub async fn login(
    state: &AppState,
    username: &str,
    password: &str,
) -> Result<User, AuthError> {

    let user =
        user_repo::find_by_username(&state.db, username)
            .await
            .map_err(|_| AuthError::InvalidCredentials)?
            .ok_or(AuthError::InvalidCredentials)?;

    if !verify_password(&user.password_hash, password) {
        return Err(AuthError::InvalidCredentials);
    }

    Ok(user)
}