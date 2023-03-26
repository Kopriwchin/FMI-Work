#include <iostream>
#include <fstream>
#include <ctime>

#include "Constants.h"

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;

unsigned computeHash(const unsigned char* memory, int length) {
	unsigned hash = 0xbeaf;

	for (int c = 0; c < length; c++) {
		hash += memory[c];
		hash += hash << 10;
		hash ^= hash >> 6;
	}

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return hash;
}

struct User {
	unsigned id;
	char name[128];
};

struct Transaction {
	unsigned sender;
	unsigned receiver;
	double coins;
	long long time;
};

struct TransactionBlock {
	unsigned id;
	unsigned prevBlockId;
	unsigned prevBlockHash;
	int validTransactions;
	Transaction transactions[16];
};

int AtoI(char* buffer)
{
	int result = 0;

	for (int i = 0; buffer[i] != '\0'; i++)
		result = result * 10 + buffer[i] - '0';

	return result;
}

bool CheckIfFileExists(const char* filePath) {
	ifstream readFile(filePath);
	if (!readFile.is_open() || !readFile)
	{
		readFile.close();
		return false;
	}
	readFile.close();

	return true;
}

int InitializeIdFile()
{
	if (CheckIfFileExists(ID_FILE_NAME))
	{
		// 10 digits in INT type
		const short BUFFER_SIZE = 10;

		ifstream idFile(ID_FILE_NAME);

		if (!idFile.is_open() || !idFile)
		{
			cout << "Invalid file!" << endl;
			return -1;
		}

		char buffer[BUFFER_SIZE];

		idFile.getline(buffer, BUFFER_SIZE);

		idFile.close();

		return AtoI(buffer);
	}
	else {
		ofstream idFile(ID_FILE_NAME);

		idFile << 1 << endl;

		idFile.close();

		return 1;
	}
}

bool IncrementId(int id)
{
	ofstream idFile(ID_FILE_NAME, ofstream::out | ofstream::trunc);

	if (!idFile.is_open() || !idFile)
	{
		cout << INVALID_FILE_MSG << endl;
		idFile.close();
		return false;
	}

	idFile << id + 1 << endl;

	idFile.close();

	return true;
}

double ExchangeCoins(const double amount) {
	const double OOPCOIN_EXCHANGE_RATE = 420;
	return amount * OOPCOIN_EXCHANGE_RATE;
}

int GetId()
{
	ifstream idFile(ID_FILE_NAME);

	if (!idFile.is_open() || !idFile)
	{
		cout << INVALID_FILE_MSG;
		idFile.close();
		return -1;
	}

	char buffer[BUFFER_SIZE];

	idFile.getline(buffer, BUFFER_SIZE);

	idFile.close();

	int idResult = AtoI(buffer);
	IncrementId(idResult);

	return idResult;
}

bool CreateUser(const char* username, const double amount) {
	const unsigned currentUserId = GetId();

	User user = { currentUserId, ""};
	strcpy_s(user.name, username);

	ofstream writeFile("users.dat", std::ios::binary | std::ios::app);

	if (!writeFile.is_open() || !writeFile)
	{
		cout << INVALID_FILE_MSG << endl;
		return -1;
	}

	writeFile.write(reinterpret_cast<const char*>(&user.id), sizeof(int));

	int nameLength = strlen(user.name);

	writeFile.write(reinterpret_cast<const char*>(&user.name), nameLength);

	writeFile.close();

	Transaction initTransaction { 0, currentUserId, ExchangeCoins(amount), std::time(nullptr) };

	return true;
}

void AddTransactionToBlock(Transaction& transaction) {

}

void InitializeBlockFile() {

	if (!CheckIfFileExists(BLOCKS_FILE_NAME))
	{
		ofstream writeFile(BLOCKS_FILE_NAME, std::ios::binary);

		writeFile.close();
	}
}

//void TransferCoins(const unsigned senderId, const unsigned receiverId) {
//	
//}

void PrintProgramCommands()
{
	cout << '\n';
	cout << "Exit program -> 0" << endl;
	cout << "Create user -> 1" << endl;
	cout << "Remove user -> 2" << endl;
	cout << "Send coins -> 3" << endl;
	cout << "Enter a command by its number: ";
}

int main() {
	cout << "Welcome to OOP-Coin!" << endl;

	PrintProgramCommands();
	
	InitializeIdFile();
	InitializeBlockFile();

	int chosenCommand;

	cin >> chosenCommand;

	while (chosenCommand)
	{
		switch (chosenCommand)
		{
			char username[128];
			case 1:
				cout << "Enter username: ";
				cin >> username;

				cout << "Enter amount: ";
				double amount;
				cin >> amount;

				CreateUser(username, amount);
				break;

			case 2:
				cout << "Enter username: ";
				cin >> username;

				// RemoveUser(username);
				break;
			case 3:
				cout << "Enter sender's username: ";
				char senderName[128];
				cin >> senderName;

				cout << "Enter receiver's name: ";
				char receiverName[128];
				cin >> username;

				// SendCoins(senderName, receiverName, amount);
			default:
				cout << "Invalid command!" << endl;
				break;
		}
		PrintProgramCommands();
		cin >> chosenCommand;
	}

	cout << "Exiting program.." << endl;
	
	return 0;
}