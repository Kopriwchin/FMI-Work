use uuid::Uuid;

pub struct Session {
    pub id: String,
    pub user_id: Option<String>,
}

impl Session {

    pub fn new() -> Self {

        Self {
            id: Uuid::new_v4().to_string(),
            user_id: None
        }
    }

    pub fn is_authenticated(&self) -> bool {
        self.user_id.is_some()
    }
}

pub fn require_auth(session: &Session) -> Result<&String, String> {

    session
        .user_id
        .as_ref()
        .ok_or("authentication required".to_string())
}

