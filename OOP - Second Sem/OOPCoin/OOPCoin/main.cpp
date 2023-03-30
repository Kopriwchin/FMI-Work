#include <iostream>
#include <fstream>
#include <ctime>

#include "Constants.h"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;


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

User loadedUsers[4];

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

int aToI(char* buffer) {
	int result = 0;

	for (int i = 0; buffer[i] != '\0'; i++)
		result = result * 10 + buffer[i] - '0';

	return result;
}

bool checkIfReadFileExists(std::ifstream &file) {
	if (!file.is_open() || !file) {
		file.close();
		return false;
	}

	return true;
}

bool checkIfWriteFileExists(std::ofstream& file) {
	if (!file.is_open() || !file) {
		file.close();
		return false;
	}

	return true;
}

int initializeIdFile() {
	ifstream idFile(ID_FILE_NAME);

	if (checkIfReadFileExists(idFile)) {
		// 10 digits in INT type
		const short BUFFER_SIZE = 10;


		if (!idFile.is_open() || !idFile) {
			cout << "Invalid file!" << endl;
			idFile.close();
			return -1;
		}

		char buffer[BUFFER_SIZE];

		idFile.getline(buffer, BUFFER_SIZE);

		idFile.close();

		return aToI(buffer);
	}
	else {
		ofstream idFile(ID_FILE_NAME);

		idFile << 1 << endl;

		idFile.close();

		return 1;
	}
}

bool incrementId(int id) {
	ofstream idFile(ID_FILE_NAME, ofstream::trunc);

	if (!idFile.is_open() || !idFile) {
		cout << INVALID_FILE_MSG << endl;
		idFile.close();
		return false;
	}

	idFile << id + 1 << endl;

	idFile.close();

	return true;
}

unsigned getId() {
	ifstream idFile(ID_FILE_NAME);

	if (!idFile.is_open() || !idFile) {
		cout << INVALID_FILE_MSG;
		idFile.close();
		return -1;
	}

	char buffer[BUFFER_SIZE];

	idFile.getline(buffer, BUFFER_SIZE);

	idFile.close();

	int idResult = aToI(buffer);
	incrementId(idResult);

	return idResult;
}

bool isTransactionValid(Transaction& transaction) {
	if (transaction.sender == 0) {
		return true;
	}

	/*ifstream usersFile("users.bat", std::ios::binary);
	while (!usersFile.eof()) {
		User user = {};
		usersFile.read((char*)&user.name, sizeof(User));
	}

	if (transaction.sender.exists)
	{

	}*/

	//Otherwise check if sender has enough money

	return true;
}

void addTransactionToBlock(Transaction& transaction) {
	if (isTransactionValid(transaction)) {
		if (true) {

		}
	}
	else {

	}
}

bool createUser(const char* username, const double amount) {
	const unsigned currentUserId = getId();

	User user = { currentUserId, ""};
	strcpy_s(user.name, username);

	ofstream writeFile(USERS_FILE_NAME, std::ios::binary | std::ios::app);

	if (!writeFile.is_open() || !writeFile)
	{
		cout << INVALID_FILE_MSG << endl;
		return false;
	}

	writeFile.write(reinterpret_cast<const char*>(&user), sizeof(User));

	writeFile.close();

	Transaction initTransaction { 0, currentUserId, ExchangeCoins(amount), std::time(nullptr) };
	addTransactionToBlock(initTransaction);
	return true;
}

double getUserAvailableCoins(unsigned id) {
	ifstream blocksFile("blocks.dat", std::ios::binary);

	return 0;
}

//void PrintWealthiestUsers(int resultsCount) {
//	// TODO
//	
//}
//void PrintBiggestBlocks(int resultsCount) {
//	// TODO
//}

void initializeBlockFile() {
	ofstream writeFile(BLOCKS_FILE_NAME, std::ios::binary);

	if (!checkIfWriteFileExists(writeFile))
	{

		writeFile.close();
	}
}
int getCountUsers()
{
	ifstream readFile(USERS_FILE_NAME, std::ios::binary);

	if (!checkIfReadFileExists(readFile))
	{
		return -1;
	}
	readFile.seekg(0, std::ios::end);
	int usersCount = readFile.tellg() / sizeof(User);

	readFile.close();

	return usersCount;
}

//User* loadUsers() {
//	int usersCount = countUsers();
//	ifstream readFile(USERS_FILE_NAME, std::ios::binary);
//
//	User* users = new User[usersCount];
//
//	if (usersCount != -1)
//	{
//		for (int i = 0; i < usersCount; i++)
//		{
//			User initUser;
//			readFile.read(reinterpret_cast<char*>(&initUser), sizeof(User));
//			users[i] = initUser;
//			cout << loadedUsers[i].id << endl;
//			cout << loadedUsers[i].name << endl;
//		}
//
//	}
//
//	readFile.close();
//
//	return users;
//}

//bool findUserByName(char* username) {
//	ifstream usersFile("users.bat", std::ios::binary);
//	User user;
//	while (!usersFile.eof())
//	{
//		usersFile.read(reinterpret_cast<char*>(&user), sizeof(User));
//		if (true)
//		{
//
//		}
//	}
//}
	
//User findUserById(unsigned id) {
//
//}

void removeUser(char* username) {
	ifstream readFile(USERS_FILE_NAME, std::ios::binary);
	int countUsers = getCountUsers();
	bool isUserFound = false;

	if (countUsers != -1) {
		ofstream writeFile(INITUSERS_FILE_NAME, std::ios::binary);

		for (int i = 1; i <= countUsers; i++) {
			User initUser;
			readFile.read(reinterpret_cast<char*>(&initUser), sizeof(User));

			// Copy every user into another file, excluding the user, that we want to delete
			if (strcmp(initUser.name, username) != 0) {
				writeFile.write(reinterpret_cast<const char*>(&initUser), sizeof(User));
			}
			else {
				isUserFound = true;
			}
		}

		// Delete users.bat file and renaming the initial file to users.bat
		if (isUserFound) {
			readFile.close();
			writeFile.close();

			if (remove(USERS_FILE_NAME)) {
				cout << "Error deleting!" << endl; 
				return;
			}

			if (std::rename(INITUSERS_FILE_NAME, USERS_FILE_NAME)) {
				cout << "Error renaming!" << endl;
				return;
			}
		}
		else {
			cout << "User does not exist!" << endl;
		}
	}
}


//void TransferCoins(const unsigned senderId, const unsigned receiverId) {
//	
//}

void validateAmount(double& amount) {
	while (true)
	{
		if (amount < 0)
		{
			cout << "Invalid input! Amount must be a positive number!" << endl;
			cin >> amount;
			continue;
		}
		break;
	}
}

void validateName(char* name) {
	while (true)
	{
		if (strlen(name) < 4 || strlen(name) > 126)
		{
			cout << "Invalid input! Name length must be more between 4 and 126 characters!" << endl;
			cin >> name;
			continue;
		}
		break;
	}
}

void printProgramCommands()
{
	cout << '\n';
	cout << "Exit program -> 0" << endl;
	cout << "Create user -> 1" << endl;
	cout << "Remove user -> 2" << endl;
	cout << "Send coins -> 3" << endl;
	cout << "Print out wealthiest users -> 4" << endl;
	cout << "Print out biggest blocks -> 5" << endl << endl;
	cout << "Enter a command by its number: ";
}

int main() {
	cout << "Welcome to OOP-Coin!" << endl;

	printProgramCommands();
	
	initializeIdFile();

	int chosenCommand;

	cin >> chosenCommand;

	while (chosenCommand)
	{
		switch (chosenCommand)
		{
			char username[128];
			double amount;

			case 1:
				cout << "Enter username: ";
				cin >> username;
				validateName(username);

				cout << "Enter amount: ";
				cin >> amount;
				validateAmount(amount);

				createUser(username, amount);
				break;
			case 2:
				cout << "Enter username: ";
				cin >> username;
				validateName(username);

				removeUser(username);
				break;
			case 3:
				cout << "Enter sender's username: ";
				char senderName[128];
				cin >> senderName;
				validateName(senderName);

				cout << "Enter receiver's name: ";
				char receiverName[128];
				cin >> receiverName;
				validateName(receiverName);
				
				// SendCoins(senderName, receiverName, amount);
				break;
			case 4:
				cout << "Enter amount of users shown: ";
				cin >> amount;
				validateAmount(amount);
				//PrintWealthiestUsers(int amount);
				break;
			case 5:
				cout << "Enter amount of users shown: ";
				cin >> amount;
				validateAmount(amount);
				//PrintBiggestBlocks(int amount);
				break;
			default:
				cout << "Invalid command!" << endl;
				break;
		}
		printProgramCommands();
		cin >> chosenCommand;
	}

	cout << "Exiting program.." << endl;
	
	return 0;
}