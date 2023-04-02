#include <iostream>
#include <fstream>
#include <ctime>

#include "Constants.h"
#include "Validation.h"

#pragma warning(disable : 4996)

using std::cin;
using std::cout;
using std::endl;
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

struct UserWithAmount {
	User user;
	double amount;
};

struct TransactionBlockWithAmount {
	TransactionBlock block;
	double amount;
};

char* iToA(long long number, short numLength) {

	char* numberToStr = new char[numLength + 1];

	for (int i = numLength - 1; i >= 0; i--) {
		short numberLastDigit = number % 10;
		number /= 10;
		numberToStr[i] = '0' + (char)numberLastDigit;
	}

	return numberToStr;
}

bool checkIfFileExists(ifstream& file) {
	if (!file.is_open() || !file) {
		return false;
	}

	return true;
}

int getCountUsers(ifstream& usersFile) {

	if (!checkIfFileExists(usersFile))
		return 0;

	usersFile.seekg(0, std::ios::end);
	unsigned usersCount = usersFile.tellg() / sizeof(User);
	usersFile.seekg(0);

	return usersCount;
}

int getCountBlocks(ifstream& blocksFile) {
	if (!checkIfFileExists(blocksFile))
		return -1;

	blocksFile.seekg(0, std::ios::end);
	unsigned blocksCount = blocksFile.tellg() / sizeof(TransactionBlock);
	blocksFile.seekg(0, std::ios::beg);

	return blocksCount;
}

bool findUserByName(char* username) {
	ifstream usersFile(USERS_FILE_NAME, std::ios::binary);
	User initUser;
	int countUsers = getCountUsers(usersFile);

	for (size_t i = 0; i < countUsers; i++) {
		usersFile.read(reinterpret_cast<char*>(&initUser), sizeof(User));

		if (strcmp(initUser.name, username) == 0)
			return true;
	}

	return false;
}

bool findUserById(unsigned id) {
	ifstream usersFile(USERS_FILE_NAME, std::ios::binary);
	User initUser;
	int countUsers = getCountUsers(usersFile);

	for (size_t i = 0; i < countUsers; i++)
	{
		usersFile.read(reinterpret_cast<char*>(&initUser), sizeof(User));
		if (initUser.id == id)
			return true;
	}

	return false;
}

void initializeBlocksFile() {
	ifstream blocksFile(BLOCKS_FILE_NAME, std::ios::binary);

	if (!checkIfFileExists(blocksFile)) {
		blocksFile.close();
		ofstream newBlocksFile(BLOCKS_FILE_NAME, std::ios::binary);
		TransactionBlock block{ 1, 1, 1, 0, NULL };
		newBlocksFile.write(reinterpret_cast<char*>(&block), sizeof(TransactionBlock));
	}
}

bool verifyBlocks() {
	ifstream blocksFile(BLOCKS_FILE_NAME, std::ios::binary);

	if (!checkIfFileExists(blocksFile))
		return true;

	int blocksCount = getCountBlocks(blocksFile);

	TransactionBlock block;
	blocksFile.read(reinterpret_cast<char*>(&block), sizeof(TransactionBlock));

	if (block.id != block.prevBlockId)
		return false;

	unsigned initHash = computeHash((const unsigned char*)&block, sizeof(TransactionBlock));

	for (int i = 0; i < blocksCount - 1; i++) {
		blocksFile.read(reinterpret_cast<char*>(&block), sizeof(TransactionBlock));

		if (block.prevBlockHash != initHash)
			return false;

		if (block.validTransactions == 0)
			return false;
	}

	return true;
}

double getUserAvailableCoins(unsigned id) {
	ifstream blocksFile(BLOCKS_FILE_NAME, std::ios::binary);

	if (!checkIfFileExists(blocksFile)) {
		cout << INVALID_FILE_MSG << endl;
		return 0;
	}

	if (!findUserById(id)) {
		cout << "User not found!" << endl;
		return 0;
	}

	double userCoins = 0;

	TransactionBlock block;
	int countBlocks = getCountBlocks(blocksFile);

	for (int i = 0; i < countBlocks; i++) {
		blocksFile.read(reinterpret_cast<char*>(&block), sizeof(TransactionBlock));

		for (size_t i = 0; i < block.validTransactions; i++) {
			if (block.transactions[i].receiver == id) {
				userCoins += block.transactions[i].coins;
			}
			else if (block.transactions[i].sender == id) {
				userCoins -= block.transactions[i].coins;
			}
		}
	}

	return userCoins;
}

double getSumOfTransactionCoinsInSingleBlock(unsigned id) {
	ifstream blocksFile(BLOCKS_FILE_NAME, std::ios::binary);

	if (!checkIfFileExists(blocksFile)) {
		cout << INVALID_FILE_MSG << endl;
		return 0;
	}

	if (!findUserById(id)) {
		cout << "User not found!" << endl;
		return 0;
	}

	double blockCoins = 0;
	int blockCount = getCountBlocks(blocksFile);
	TransactionBlock block;

	for (int i = 0; i < blockCount; i++) {
		blocksFile.read(reinterpret_cast<char*>(&block), sizeof(TransactionBlock));

		if (block.id == id) {
			for (size_t i = 0; i < block.validTransactions; i++) {
				blockCoins += block.transactions[i].coins;
			}
			return blockCoins;
		}
	}

	return blockCoins;
}

bool isTransactionValid(Transaction& transaction) {

	// If sender is 0, the transaction is most likely an initial one (from creating an user)
	// Since we cannot be 100% sure, we also check if the receiver is a valid and existing person
	if (transaction.sender == 0)
		return findUserById(transaction.receiver);

	if (transaction.receiver == 0)
		return findUserById(transaction.sender);

	if (!findUserById(transaction.sender)) {
		cout << "Sender does not exist!" << endl;
		return false;
	}

	if (!findUserById(transaction.receiver)) {
		cout << "Receiver does not exist!" << endl;
		return false;
	}

	if (getUserAvailableCoins(transaction.sender) < transaction.coins) {
		cout << "User with id " << transaction.sender << " has insufficient coins to make the transaction!" << endl;
		return false;
	}

	return true;
}

bool addTransactionToBlock(Transaction& transaction) {
	if (isTransactionValid(transaction)) {
		ifstream blocksReadFile(BLOCKS_FILE_NAME, std::ios::binary);
		TransactionBlock block;

		/*A safety measure so we can be sure that if we would've been given a blocks.dat to work
		with that has blocks, that aren't filled with the maximal size of transactions (16) in a
	   single block, it would start filling the last block, setting correct work of the program*/
		blocksReadFile.seekg(-(int)(sizeof(TransactionBlock)), std::ios::end);
		blocksReadFile.read(reinterpret_cast<char*>(&block), sizeof(TransactionBlock));
		blocksReadFile.close();

		if (block.validTransactions < 16) {
			block.transactions[block.validTransactions] = transaction;
			block.validTransactions++;

			ofstream blocksWriteFile(BLOCKS_FILE_NAME, std::ios::binary | std::ios::ate | std::ios::in);
			blocksWriteFile.seekp(-(int)(sizeof(TransactionBlock)), std::ios::end);
			blocksWriteFile.write(reinterpret_cast<const char*>(&block), sizeof(TransactionBlock));
			blocksWriteFile.seekp(-(int)(sizeof(Transaction) * 16), std::ios::end);

			for (size_t i = 0; i < block.validTransactions; i++) {
				blocksWriteFile.write(reinterpret_cast<const char*>(&block.transactions[i]), sizeof(Transaction));
			}
		}
		else {
			ofstream blocksWriteFile(BLOCKS_FILE_NAME, std::ios::binary | std::ios::ate | std::ios::in);
			TransactionBlock newBlock{ block.id + 1, block.id, computeHash((const unsigned char*)&block, sizeof(TransactionBlock)), 1, 0 };
			blocksWriteFile.write(reinterpret_cast<const char*>(&newBlock), sizeof(TransactionBlock));
			blocksWriteFile.seekp(-(int)(sizeof(Transaction) * 16), std::ios::end);
			blocksWriteFile.write(reinterpret_cast<const char*>(&transaction), sizeof(Transaction));
		}

		return true;
	}
	else
		return false;
}

short getNumberLength(long long time)
{
	short count = 0;

	while (time != 0) {
		time /= 10;
		count++;
	}

	return count;
}

void swapUsers(UserWithAmount& user1, UserWithAmount& user2) {
	UserWithAmount initUser = user1;
	user1 = user2;
	user2 = initUser;
}

void swapBlocks(TransactionBlockWithAmount& block1, TransactionBlockWithAmount& block2) {
	TransactionBlockWithAmount initBlock = block1;
	block1 = block2;
	block2 = initBlock;
}

void sortUsersByAmount(UserWithAmount* users, int usersCount)
{
	int i, j;
	bool swapped;
	for (i = 0; i < usersCount - 1; i++) {
		swapped = false;
		for (j = 0; j < usersCount - i - 1; j++) {
			if (users[j].amount < users[j + 1].amount) {
				swapUsers(users[j], users[j + 1]);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

void sortBlocksByAmount(TransactionBlockWithAmount* blocks, int blocksCount) {

	int i, j;
	bool swapped;
	for (i = 0; i < blocksCount - 1; i++) {
		swapped = false;
		for (j = 0; j < blocksCount - i - 1; j++) {
			if (blocks[j].amount < blocks[j + 1].amount) {
				swapBlocks(blocks[j], blocks[j + 1]);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

char* createWealthiestUserFileName() {
	long long time = std::time(nullptr);
	int timeLength = getNumberLength(time);

	// 40, because strlen("wealthiest-users") is 16, long long can be as much as 19 numbers, strlen(".txt") is 4, null terminator is 1 -> 16 + 19 + 4 + 1

	char fullFileName[40] = "wealthiest-users";
	char* timeStr = iToA(time, timeLength);

	int i = 0;
	int j = 0;

	for (i = 0, j = 16; i < timeLength; i++, j++)
		fullFileName[j] = timeStr[i];

	fullFileName[j++] = '.';
	fullFileName[j++] = 't';
	fullFileName[j++] = 'x';
	fullFileName[j++] = 't';

	fullFileName[39] = '\0';
	delete[] timeStr;

	return fullFileName;
}

char* createBiggestBlockFileName() {
	long long time = std::time(nullptr);
	int timeLength = getNumberLength(time);

	// 38, because strlen("biggest-blocks") is 14, long long can be as much as 19 numbers, strlen(".txt") is 4, null terminator is 1 -> 14 + 19 + 4 + 1

	char fullFileName[38] = "biggest-blocks";
	char* timeStr = iToA(time, timeLength);

	int i = 0;
	int j = 0;

	for (i = 0, j = 14; i < timeLength; i++, j++)
		fullFileName[j] = timeStr[i];

	fullFileName[j++] = '.';
	fullFileName[j++] = 't';
	fullFileName[j++] = 'x';
	fullFileName[j++] = 't';

	fullFileName[37] = '\0';
	delete[] timeStr;

	return fullFileName;
}

void printWealthiestUsers(int resultsCount) {
	if (resultsCount == 0) {
		cout << "No information to show!" << endl;
		return;
	}

	ifstream blocksFile(BLOCKS_FILE_NAME, std::ios::binary);
	ifstream usersFile(USERS_FILE_NAME, std::ios::binary);

	if (!checkIfFileExists(blocksFile)) {
		cout << INVALID_FILE_MSG << endl;
		return;
	}

	if (!checkIfFileExists(usersFile))
	{
		cout << "No users currently in the database!" << endl;
		return;
	}

	int usersCount = getCountUsers(usersFile);

	TransactionBlock block;
	UserWithAmount* users = new UserWithAmount[usersCount];
	User initUser;

	blocksFile.read(reinterpret_cast<char*>(&block), sizeof(TransactionBlock));

	for (size_t i = 0; i < usersCount; i++) {
		usersFile.read(reinterpret_cast<char*>(&initUser), sizeof(User));
		users[i].user = initUser;
		users[i].amount = getUserAvailableCoins(initUser.id);
	}

	sortUsersByAmount(users, usersCount);

	if (resultsCount > usersCount)
		resultsCount = usersCount;

	char* fullFileName = createWealthiestUserFileName();
	char fullName[40];
	strcpy(fullName, fullFileName);

	ofstream wealthiestUsersFile(fullName, std::ios::binary | std::ios::trunc);

	for (size_t i = 0; i < resultsCount; i++) {
		wealthiestUsersFile << i + 1 << ".\tUsername: " << users[i].user.name << "\tAmount coins: " << users[i].amount << endl;
	}
	delete[] users;

	cout << "Successfully generated file with the top " << resultsCount << " users!" << endl;
}

void printBiggestBlocks(int resultsCount) {
	if (resultsCount == 0) {
		cout << "No information to show!" << endl;
		return;
	}

	ifstream blocksFile(BLOCKS_FILE_NAME, std::ios::binary);

	if (!checkIfFileExists(blocksFile)) {
		cout << INVALID_FILE_MSG << endl;
		return;
	}

	TransactionBlock block;
	int blocksCount = getCountBlocks(blocksFile);

	TransactionBlockWithAmount* blocksWithAmount = new TransactionBlockWithAmount[blocksCount];

	for (int i = 0; i < blocksCount; i++) {
		blocksFile.read(reinterpret_cast<char*>(&block), sizeof(TransactionBlock));
		blocksWithAmount[i].block = block;
		blocksWithAmount[i].amount = getSumOfTransactionCoinsInSingleBlock(block.id);
	}

	if (resultsCount > blocksCount)
		resultsCount = blocksCount;

	char* fullFileName = createBiggestBlockFileName();
	char fullName[38];
	strcpy(fullName, fullFileName);

	ofstream biggestBlocksFile(fullName, std::ios::binary | std::ios::trunc);

	sortBlocksByAmount(blocksWithAmount, blocksCount);

	for (size_t i = 0; i < resultsCount; i++) {
		biggestBlocksFile << i + 1 << ".\tBlock ID: " << blocksWithAmount[i].block.id << "\tTotal amount of coins: " << blocksWithAmount[i].amount << endl;
	}
	delete[] blocksWithAmount;

	cout << "Successfully generated file with the top " << resultsCount << " blocks!" << endl;
}

bool sendCoins(unsigned senderId, unsigned receiverId, double amount) {
	Transaction transaction{ senderId, receiverId, amount, std::time(nullptr) };

	if (isTransactionValid(transaction)) {
		addTransactionToBlock(transaction);
		return true;
	}
	else
		return false;
}

bool removeUser(char* username) {

	if (!findUserByName(username)) {
		cout << "\t\tUser does not exist!" << endl;
		return false;
	}

	ifstream readFile(USERS_FILE_NAME, std::ios::binary);
	int countUsers = getCountUsers(readFile);

	if (countUsers != 0) {
		ofstream writeFile(INITUSERS_FILE_NAME, std::ios::binary);

		for (int i = 1; i <= countUsers; i++) {
			User initUser;
			readFile.read(reinterpret_cast<char*>(&initUser), sizeof(User));

			// Copy every user into another file, excluding the user, that we want to delete
			if (strcmp(initUser.name, username) != 0) {
				writeFile.write(reinterpret_cast<const char*>(&initUser), sizeof(User));
			}
			else {
				sendCoins(initUser.id, 0, getUserAvailableCoins(initUser.id));
			}
		}

		// Delete "users.dat" file and renaming the initial file to "users.dat"
		readFile.close();
		writeFile.close();

		if (remove(USERS_FILE_NAME)) {
			cout << "\t\tError deleting " << USERS_FILE_NAME << " file!" << endl;
			return true;
		}

		if (std::rename(INITUSERS_FILE_NAME, USERS_FILE_NAME)) {
			cout << "\t\tError renaming " << INITUSERS_FILE_NAME << " to " << USERS_FILE_NAME << endl;
			return true;
		}
	}
}

unsigned getId() {
	ifstream blocksFile(BLOCKS_FILE_NAME, std::ios::binary);

	if (!blocksFile.is_open() || !blocksFile) {
		cout << INVALID_FILE_MSG;
		return -1;
	}

	int blocksCount = getCountBlocks(blocksFile);
	int biggestId = 0;
	TransactionBlock block;

	for (int i = 0; i < blocksCount; i++) {
		blocksFile.read(reinterpret_cast<char*>(&block), sizeof(TransactionBlock));

		for (int j = 0; j < block.validTransactions; j++)
		{
			if (block.transactions[j].receiver > biggestId)
			{
				biggestId = block.transactions[j].receiver;
			}
		}
	}

	return biggestId + 1;
}

bool createUser(char* username, const double amount) {
	if (findUserByName(username)) {
		cout << "\t\tUsername is already being used!" << endl;
		return false;
	}

	const unsigned currentUserId = getId();

	User user = { currentUserId, "" };
	strcpy(user.name, username);

	ofstream writeFile(USERS_FILE_NAME, std::ios::binary | std::ios::app);

	if (!writeFile.is_open() || !writeFile) {
		cout << INVALID_FILE_MSG << endl;
		return false;
	}

	writeFile.write(reinterpret_cast<const char*>(&user), sizeof(User));

	writeFile.close();

	Transaction initTransaction{ 0, currentUserId, ExchangeCoins(amount), std::time(nullptr) };
	addTransactionToBlock(initTransaction);

	return true;
}

void printProgramCommands()
{
	cout << '\n';
	cout << "----------------------------------------------------" << endl;
	cout << "Exit program -> 0" << endl;
	cout << "Create user -> 1" << endl;
	cout << "Remove user -> 2" << endl;
	cout << "Send coins -> 3" << endl;
	cout << "Print out wealthiest users -> 4" << endl;
	cout << "Print out biggest blocks -> 5" << endl;
	cout << "Verify transactions -> 6" << endl << endl;
	cout << "Enter a command by its number: ";
}

int main() {
	cout << "\t\tWelcome to OOP-Coin!" << endl;

	printProgramCommands();

	initializeBlocksFile();


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

			if (createUser(username, amount))
				cout << "\t\tSuccessfully created a user!" << endl;
			else
				cout << "\t\tCreating a user was unsuccessful!" << endl;

			break;
		case 2:
			cout << "Enter username: ";
			cin >> username;
			validateName(username);

			if (removeUser(username))
				cout << "\t\tUser successfully deleted!" << endl;
			else
				cout << "\t\tRemoving the user was unsuccessful!" << endl;

			break;
		case 3:
			cout << "Enter sender's id: ";
			unsigned senderId;
			cin >> senderId;
			if (!cin)
			{
				cout << "Invalid input!" << endl;
				return -1;
			}

			cout << "Enter receiver's id: ";
			unsigned receiverId;
			cin >> receiverId;
			if (!cin)
			{
				cout << "Invalid input!" << endl;
				return -1;
			}

			cout << "Enter amount: ";
			cin >> amount;
			if (!cin)
			{
				cout << "Invalid input!" << endl;
				return -1;
			}

			validateAmount(amount);
			if (sendCoins(senderId, receiverId, amount))
				cout << "\t\tTransaction was successful!" << endl;
			else
				cout << "\t\tTransaction was not successful!" << endl;

			break;
		case 4:
			cout << "Enter amount of users that should be displayed: ";
			cin >> amount;
			if (!cin)
			{
				cout << "Invalid input!" << endl;
				return -1;
			}

			validateAmount(amount);
			printWealthiestUsers(amount);
			break;
		case 5:
			cout << "Enter amount of blocks that should be displayed: ";
			cin >> amount;
			if (!cin)
			{
				cout << "Invalid input!" << endl;
				return -1;
			}
			validateAmount(amount);
			printBiggestBlocks(amount);
			break;
		case 6:
			if (verifyBlocks())
				cout << "Data in the file \"blocks.dat\" are valid!" << endl;
			else
				cout << "Data in the file \"blocks.dat\" are invalid!" << endl;

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