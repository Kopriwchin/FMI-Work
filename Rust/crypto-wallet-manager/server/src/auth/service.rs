use uuid::Uuid;

use crate::auth::password::{hash_password, verify_password};
use crate::db::user_repo;
use crate::errors::AuthError;

use common::models::User;

pub fn register(username: &str, password: &str) -> Result<(), AuthError> {

    if user_repo::find_by_username(username).is_some() {
        return Err(AuthError::InvalidCredentials);
    }

    let hashed: String =
        hash_password(password).map_err(|_| AuthError::InvalidCredentials)?;

    let user: User = User {
        id: Uuid::new_v4().to_string(),
        username: username.to_string(),
        password_hash: hashed,
    };

    user_repo::create_user(user)
        .map_err(|_| AuthError::InvalidCredentials)?;

    Ok(())
}

pub fn login(username: &str, password: &str) -> Result<User, AuthError> {

    let user: User = match user_repo::find_by_username(username) {

        Some(u) => u,
        None => return Err(AuthError::InvalidCredentials)
    };

    if !verify_password(&user.password_hash, password) {
        return Err(AuthError::InvalidCredentials);
    }

    Ok(user)
}
