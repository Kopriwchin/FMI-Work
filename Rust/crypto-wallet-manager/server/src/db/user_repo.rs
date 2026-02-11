use std::collections::HashMap;
use std::fs;

use common::models::User;

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

pub fn find_by_username(username: &str) -> Option<User> {

    let users: HashMap<String, User> = load_users();

    users.get(username).cloned()
}

pub fn create_user(user: User) -> Result<(), String> {

    let mut users: HashMap<String, User> = load_users();

    if users.contains_key(&user.username) {
        return Err("user already exists".to_string());
    }

    users.insert(user.username.clone(), user);

    save_users(&users)
        .map_err(|_| "failed to save user".to_string())
}
