use argon2::{
    password_hash::{SaltString, PasswordHasher, PasswordVerifier, PasswordHash},
    Argon2
};
use rand::rngs::OsRng;

pub fn hash_password(password: &str) -> Result<String, String> {

    let salt: SaltString = SaltString::generate(&mut OsRng);

    let argon2: Argon2 = Argon2::default();

    let hash = argon2
        .hash_password(password.as_bytes(), &salt)
        .map_err(|_| "hash error".to_string())?
        .to_string();

    Ok(hash)
}

pub fn verify_password(hash: &str, password: &str) -> bool {

    let parsed_hash: PasswordHash = match PasswordHash::new(hash) {
        Ok(h) => h,
        Err(_) => return false
    };

    Argon2::default()
        .verify_password(password.as_bytes(), &parsed_hash)
        .is_ok()
}
