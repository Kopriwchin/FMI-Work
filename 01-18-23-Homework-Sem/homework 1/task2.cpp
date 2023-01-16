#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

void BruteForceDecryptCipher(const char* cipherText)
{
	cout << endl;

	int textLength = strlen(cipherText);

	int startIndex = 65;
	int endIndex = 90;
	char* decryptedText = new char[textLength];

	if (textLength >= 1024)
	{
		cout << "Text too long!";
		return;
	}

	for (size_t i = 0; i < 26; i++)
	{
		cout << "plain text for key " << i << " :- ";

		for (size_t j = 0; j < textLength; j++)
		{
			if (cipherText[j] == ' ')
			{
				cout << ' ';
				continue;
			}

			if (cipherText[j] < 65 || 95 < cipherText[j])
			{
				cout << "\nNext character " << "\'" << cipherText[j] << "\'" << " is invalid! " << "Only capital letters allowed!";
				return;
			}

			int letterIndex = cipherText[j] - i;

			if (!(startIndex <= letterIndex && letterIndex <= endIndex))
			{
				letterIndex += 26;
			}

			cout << char(letterIndex);
		}

		cout << endl;
	}

	delete[] decryptedText;
}

int main()
{
	/* // Test example of the program
	char input1[] = "FTUE UE MZ QJMYBXQ YQEEMSQ FA NQ QZODKBFQP";

	char input2[] = "AcBC";

	BruteForceDecryptCipher(input1);
	// correct output, works as intended
	cout << endl;

	BruteForceDecryptCipher(input2);
	// empty output, because of the if-statement on line 30 
	// (if the letter is not of the correct type, mark it as a wrong input and return)
	cout << endl; */

	cout << "Enter an input: " << endl;
	string inputStr;

	std::getline(cin, inputStr);

	const char* inputAsArr = inputStr.c_str();

	BruteForceDecryptCipher(inputAsArr);
}