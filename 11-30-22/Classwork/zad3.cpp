#include <iostream>
using namespace std;

char* replaceChars(char* word, char symbol, char evenSymbol, char oddSymbol) {
	
	for (int i = 0; i < strlen(word); i++)
	{
		if (word[i] == symbol)
		{
			if ((i + 1) % 2 == 0)
			{
				word[i] = evenSymbol;
			}
			else {
				word[i] = oddSymbol;
			}
		}
	}

	return word;
}

int main()
{
	char str[100] = "H_ll_  my fri_nd";
	char replaceSymbol, evenSymbol, oddSymbol;

	cin >> replaceSymbol;
	cin >> evenSymbol;
	cin >> oddSymbol;

	cout << replaceChars(str, replaceSymbol, evenSymbol, oddSymbol);
}