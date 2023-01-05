#include <iostream>
using std::cin;
using std::cout;
using std::endl;

char* Encrypt(unsigned int key, const char* message)
{
	char* encryptedMessage = new char[1024];

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

		int newLetterCode = message[i] + key;

		if (!(startIndex <= newLetterCode && newLetterCode <= endIndex))
		{
			newLetterCode -= 26;
		}
		encryptedMessage[i] = char(newLetterCode);
	}

	encryptedMessage[i++] = '\0';

	return encryptedMessage;
}

char* Decrypt(unsigned int key, char* message)
{
	char* decryptedMessage = new char[1024];

	if (strlen(message) >= 1024)
	{
		cout << "Message too long!";
		return decryptedMessage;
	}

	size_t i;
	int startIndex = 65;
	int endIndex = 90;

	for (i = 0; i < strlen(message); i++)
	{
		if (message[i] == ' ')
		{
			decryptedMessage[i] = ' ';
			continue;
		}

		int newLetterCode = message[i] - key;

		if (!(startIndex <= newLetterCode && newLetterCode <= endIndex))
		{
			newLetterCode += 26;
		}
		decryptedMessage[i] = char(newLetterCode);
	}

	decryptedMessage[i++] = '\0';

	return decryptedMessage;
}

int main()
{
	char toBeEncrypted[] = "THIS IS AN EXAMPLE MESSAGE TO BE ENCRYPTED";
	char toBeDecrypted[] = "MYWLYN NYRN NI VY XYWLSJNYX";

	cout << Encrypt(12, toBeEncrypted);
	cout << endl;
	cout << Decrypt(20, toBeDecrypted);
	cout << endl;
}