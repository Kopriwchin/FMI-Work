#include <iostream>
using namespace std;

char* removeRepeatingChars(char* str) {
	int count = 0;
	
	char uniqueWord[10];
	bool isRepeatedSymbol = false;
	int i, j;

	for (i = 0; i < strlen(str); i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (str[i] == uniqueWord[j])
			{
				isRepeatedSymbol = true;
				break;
			}
			else {
				isRepeatedSymbol = false;
			}
		}
		if (!isRepeatedSymbol)
		{
			uniqueWord[count] = str[i];
			cout << uniqueWord[count];
			count++;
		}
		
	}

	return uniqueWord;
}

int main()
{
	char str[100] = "cbbaghcbaj";
	removeRepeatingChars(str);
}