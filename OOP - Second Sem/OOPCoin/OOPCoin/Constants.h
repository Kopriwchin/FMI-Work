#pragma once

const short BUFFER_SIZE = 128;
const char INVALID_FILE_MSG[] = "Error! Could not open requested file!";
const char* ID_FILE_NAME = "id.txt";
const char* BLOCKS_FILE_NAME = "blocks.dat";

double ExchangeCoins(const double amount) {
	const double OOPCOIN_EXCHANGE_RATE = 420;
	return amount * OOPCOIN_EXCHANGE_RATE;
}