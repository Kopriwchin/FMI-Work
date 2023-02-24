#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

char* Encrypt(unsigned int key, const char* message)
{
	char* encryptedMessage = new char[strlen(message)];

	if (strlen(message) >= 1024)
	{
		cout << "Message too long!";
		return encryptedMessage;
	}

	size_t i;
	int startIndex = 65;
	int endIndex = 90;

	for (i = 0; i < strlen(message); i++)
	{
		if (message[i] == ' ')
		{
			encryptedMessage[i] = ' ';
			continue;
		}

		if (startIndex > message[i] || message[i] > endIndex)
		{
			cout << "Message contains an unacceptable character. Only capital letters allowed!";
			delete[] encryptedMessage;
			exit(-1);
		}

		int newLetterCode = message[i] + key;

		if (!(startIndex <= newLetterCode && newLetterCode <= endIndex))
		{
			newLetterCode -= 26;
		}
		encryptedMessage[i] = newLetterCode;
	}

	encryptedMessage[i++] = '\0';

	return encryptedMessage;
}

char* Decrypt(unsigned int key, const char* message)
{
	// Better optimisation, no need to rewrite code
	return Encrypt(26 - key, message);
}

int main()
{
	string option;

	cin >> option;

	int key;

	if (!(cin >> key))
	{
		cout << -1;
		return -1;
	}

	string message;

	std::cin.ignore();
	std::getline(cin, message);

	const char* messageAsArr = message.c_str();
	
	if (option == "encrypt")
	{
		cout << Encrypt(key, messageAsArr);
	}
	else if (option == "decrypt")
	{
		cout << Decrypt(key, messageAsArr);
	}
	else
	{
		cout << -1;
		return -1;
	}

	return 0;
}