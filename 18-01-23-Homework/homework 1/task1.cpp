#include <iostream>
using std::cin;
using std::cout;
using std::endl;

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
	// Test example of the program
	char toBeEncrypted[] = "THIS IS AN EXAMPLE MESSAGE TO BE ENCRYPTED";
	char toBeDecrypted[] = "MYWLYN NYRN NI VY XYWLSJNYX";

	cout << Encrypt(12, toBeEncrypted);
	cout << endl;

	cout << Decrypt(20, toBeDecrypted);
	cout << endl;

	return 0;
}