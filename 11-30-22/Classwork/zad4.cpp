#include <iostream>
using namespace std;

int countMatches(char* str, char matchSymbol) {
	int count = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == matchSymbol)
		{
			count++;
		}
	}

	return count;
}

int main()
{
	char str[100] = "aabbabc11aa";
	char matchSymbol = 'a';

	cout << countMatches(str, matchSymbol);
}