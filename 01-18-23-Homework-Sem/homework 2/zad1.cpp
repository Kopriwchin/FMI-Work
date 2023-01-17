#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

string createKeyword(const string key, const string message)
{
	int intervalCount = 0;

	for (size_t i = 0; i < message.length(); i++)
	{
		if (message[i] == ' ')
		{
			intervalCount++;
		}
	}

	char* keyword = new char[message.length() - intervalCount];

	for (size_t i = 0, j = 0, keyIndex = 0; i < message.length(); i++)
	{
		if (message[i] != ' ')
		{
			if (keyIndex == key.length())
			{
				keyIndex = 0;
			}

			keyword[j] = key[keyIndex];
			keyIndex++;
			j++;
		}
	}

	string result = keyword;
	delete[] keyword;

	return result;
}

string Encrypt(const string key, const string message, bool shouldDecrypt = false)
{
	string keyword = createKeyword(key, message);

	char* encryptedMessage = new char[message.length() + 1];
	int index;

	for (size_t i = 0, j = 0; i < message.length(); i++)
	{
		if (message[i] != ' ')
		{
			if (shouldDecrypt)
			{
				int charResult = (message[i] - keyword[j]) % 26;

				if (charResult < 0)
				{
					charResult += 26;
				}

				encryptedMessage[i] = char(charResult + 65);
			}
			else
			{
				int charResult = (message[i] + keyword[j]) % 26;
				encryptedMessage[i] = char(charResult + 65);
			}


			j++;
		}
		else
		{
			encryptedMessage[i] = ' ';
		}

		index = i;
	}

	encryptedMessage[index + 1] = '\0';
	string result = encryptedMessage;
	delete[] encryptedMessage;

	return result;
}

string Decrypt(const string key, const string message)
{
	return Encrypt(key, message, true);;
}

int main()
{
	string option;

	cin >> option;

	string key;

	cin >> key;

	string message;

	std::cin.ignore();
	std::getline(cin, message);

	if (option == "encrypt")
	{
		cout << Encrypt(key, message);
	}
	else if (option == "decrypt")
	{
		cout << Decrypt(key, message);
	}
	else
	{
		cout << -1;
		return -1;
	}

	return 0;
}