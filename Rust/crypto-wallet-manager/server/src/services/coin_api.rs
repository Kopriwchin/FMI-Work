use serde::Deserialize;
use reqwest::Client;
use tokio::sync::Mutex;

use std::sync::Arc;
use std::time::{Instant, Duration};

#[derive(Deserialize, Clone)]
pub struct Asset {
    pub asset_id: String,
    pub name: Option<String>,
    pub price_usd: Option<f64>,
    pub type_is_crypto: Option<u8>,
}

pub struct AssetCache {
    pub assets: Vec<Asset>,
    pub last_update: Instant,
}

impl AssetCache {
    pub fn is_valid(&self) -> bool {
        self.last_update.elapsed() < Duration::from_secs(1800) // 30min
    }
}

pub struct CoinApiService {
    client: Client,
    api_key: String,
    cache: Arc<Mutex<Option<AssetCache>>>,
}

impl CoinApiService {
    pub fn new(api_key: String) -> Self {
        Self {
            client: Client::new(),
            api_key,
            cache: Arc::new(Mutex::new(None)),
        }
    }

    pub async fn get_assets(&self) -> Result<Vec<Asset>, reqwest::Error> {
        let mut cache_guard = self.cache.lock().await;

        if let Some(cache) = cache_guard.as_ref() {
            if cache.is_valid() {
                return Ok(cache.assets.clone());
            }
        }

        let response = self.client
            .get("https://rest.coinapi.io/v1/assets")
            .header("X-CoinAPI-Key", &self.api_key)
            .send()
            .await?
            .json::<Vec<Asset>>()
            .await?;

        let cryptos: Vec<Asset> = response
            .into_iter()
            .filter(|a| a.type_is_crypto == Some(1))
            .take(100)
            .collect();

        *cache_guard = Some(AssetCache {
            assets: cryptos.clone(),
            last_update: Instant::now(),
        });

        Ok(cryptos)
    }
}

