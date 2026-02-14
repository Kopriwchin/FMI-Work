pub struct Session {
    pub user_id: Option<String>,
}

impl Session {
    pub fn new() -> Self {

        Self {
            user_id: None,
        }
    }

    pub fn is_authenticated(&self) -> bool {
        self.user_id.is_some()
    }
}