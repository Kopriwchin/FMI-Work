use common::commands::{ClientCommand, ServerResponse};
use tokio::io::{AsyncBufReadExt, AsyncWriteExt, BufReader};
use tokio::net::TcpStream;

pub struct TcpJsonClient {
    reader: BufReader<tokio::net::tcp::OwnedReadHalf>,
    writer: tokio::net::tcp::OwnedWriteHalf,
}

impl TcpJsonClient {
    pub async fn connect(addr: &str) -> Result<TcpJsonClient, Box<dyn std::error::Error>> {
        let stream: TcpStream = TcpStream::connect(addr).await?;
        let (read_half, write_half) = stream.into_split();

        Ok(TcpJsonClient {
            reader: BufReader::new(read_half),
            writer: write_half,
        })
    }

    pub async fn send(
        &mut self,
        command: ClientCommand,
    ) -> Result<ServerResponse, Box<dyn std::error::Error>> {
        let json: String = serde_json::to_string(&command)?;
        self.writer.write_all(json.as_bytes()).await?;
        self.writer.write_all(b"\n").await?;

        let mut line: String = String::new();
        let bytes: usize = self.reader.read_line(&mut line).await?;
        if bytes == 0 {
            return Err("Server disconnected".into());
        }

        let response: ServerResponse = serde_json::from_str(line.trim())?;
        Ok(response)
    }
}
