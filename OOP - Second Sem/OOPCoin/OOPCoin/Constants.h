#pragma once

const short BUFFER_SIZE = 128;
const char INVALID_FILE_MSG[] = "\t\tError! Could not open requested file!";
const char* BLOCKS_FILE_NAME = "blocks.dat";
const char* USERS_FILE_NAME = "users.dat";
const char* INITUSERS_FILE_NAME = "initUsersFile.dat";

double ExchangeCoins(const double amount) {
	const double OOPCOIN_EXCHANGE_RATE = 420;
	return amount * OOPCOIN_EXCHANGE_RATE;
}