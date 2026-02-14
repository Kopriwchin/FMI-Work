use async_trait::async_trait;
use serde::Deserialize;
use reqwest::Client;

#[derive(Deserialize, Clone)]
pub struct Asset {
    pub asset_id: String,
    pub name: Option<String>,
    pub price_usd: Option<f64>,
    pub type_is_crypto: Option<u8>,
}

#[async_trait]
pub trait CoinApi: Send + Sync {
    async fn get_asset(&self, asset_id: &str) -> Result<Asset, reqwest::Error>;
    async fn get_assets(&self) -> Result<Vec<Asset>, reqwest::Error>;
}

pub struct CoinApiService {
    client: Client,
    api_key: String,
}

#[async_trait]
impl CoinApi for CoinApiService {
    async fn get_asset(&self, asset_id: &str) -> Result<Asset, reqwest::Error> {
        let url: String = format!("https://rest.coinapi.io/v1/assets/{}", asset_id);

        let response = self.client
            .get(url)
            .header("X-CoinAPI-Key", &self.api_key)
            .send()
            .await?
            .json::<Vec<Asset>>()
            .await?;

        Ok(response.into_iter().next().unwrap())
    }

    async fn get_assets(&self) -> Result<Vec<Asset>, reqwest::Error> {
        let response = self.client
            .get("https://rest.coinapi.io/v1/assets")
            .header("X-CoinAPI-Key", &self.api_key)
            .send()
            .await?
            .json::<Vec<Asset>>()
            .await?;

        Ok(response)
    }
}

impl CoinApiService {
    pub fn new(api_key: String) -> Self {
        Self {
            client: Client::new(),
            api_key,
        }
    }

    /// Live call: GET /v1/assets/{asset_id}
    pub async fn get_asset(
        &self,
        asset_id: &str,
    ) -> Result<Asset, reqwest::Error> {

        let url: String = format!(
            "https://rest.coinapi.io/v1/assets/{}",
            asset_id
        );

        let response = self.client
            .get(url)
            .header("X-CoinAPI-Key", &self.api_key)
            .send()
            .await?
            .json::<Vec<Asset>>()
            .await?;

        // CoinAPI returns array with 0 or 1 elements for this endpoint
        Ok(response.into_iter().next().unwrap())
    }

    pub async fn get_assets(
        &self,
    ) -> Result<Vec<Asset>, reqwest::Error> {

        let response = self.client
            .get("https://rest.coinapi.io/v1/assets")
            .header("X-CoinAPI-Key", &self.api_key)
            .send()
            .await?
            .json::<Vec<Asset>>()
            .await?;

        Ok(response)
    }
}
