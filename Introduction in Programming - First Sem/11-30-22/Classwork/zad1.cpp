#include <iostream>
using namespace std;

void printSmallLetters(char word[]) {
	int length = strlen(word);
	int index = 0;

	char* anotherWord = new char[length];

	for (int i = 0; i < length; i++)
	{
		if (word[i] < 97 || word[i] > 122)
		{
			continue;
		}
		else
		{
			anotherWord[index] = word[i];
			cout << anotherWord[index];
			index++;
		}
	}

	delete[] anotherWord;
}

int main()
{
	char str[] = "aBc!?Def";

	printSmallLetters(str);
}