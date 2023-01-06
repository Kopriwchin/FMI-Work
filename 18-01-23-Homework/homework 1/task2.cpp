#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void BruteForceDecryptCipher(char* cipherText)
{
	int startIndex = 65;
	int endIndex = 90;
	char* decryptedText = new char[1024];

	if (strlen(cipherText) >= 1024)
	{
		cout << "Text too long!";
		return;
	}

	for (size_t i = 0; i < 26; i++)
	{
		cout << "plain text for key " << i << ":- ";

		for (size_t j = 0; j < strlen(cipherText); j++)
		{
			if (cipherText[j] == ' ')
			{
				cout << ' ';
				continue;
			}

			if (cipherText[j] < 65 || 95 < cipherText[j])
			{
				cout << "Wrong input!";
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
}

int main()
{
	char input1[] = "FTUE UE MZ QJMYBXQ YQEEMSQ FA NQ QZODKBFQP";

	char input2[] = { 'a', 'b', 'c' };

	BruteForceDecryptCipher(input1);
	// correct output, works as intended
	
	cout << endl;

	BruteForceDecryptCipher(input2); 
	// empty output, because of the if-statement on line 30 
	// (if the letter is not of the correct type, mark it as a wrong input and return)

	cout << endl;
}