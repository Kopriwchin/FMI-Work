mod logger;

use thiserror::Error;

#[derive(Error, Debug)]
pub enum AuthError {

    #[error("invalid credentials")]
    InvalidCredentials,

    #[error("not authenticated")]
    NotAuthenticated,
}
