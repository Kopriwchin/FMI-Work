use std::fs::OpenOptions;
use std::io::Write;

pub fn log_error(message: &str) {

    let mut file = OpenOptions::new()
        .append(true)
        .create(true)
        .open("errors.log")
        .unwrap();

    let log = format!(
        "[{}] {}\n",
        chrono::Utc::now(),
        message
    );

    file.write_all(log.as_bytes()).ok();
}
