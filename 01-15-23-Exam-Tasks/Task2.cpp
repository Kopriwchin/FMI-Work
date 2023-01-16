#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int CapitalLettersChecker(char* word)
{
	int count = 0;

	for (size_t i = 0; i < strlen(word); i++)
	{
		if ('A' <= word[i] && word[i] <= 'Z')
		{
			count++;
		}
	}

	return count;
}

int main()
{
	int n;
	const int LENGTH = 9;
	const int ARRAY_SIZE = 50;

	char passwords[ARRAY_SIZE][ARRAY_SIZE] = {0};

	cin >> n;
	char str[LENGTH];

	for (size_t i = 0; i < n; i++)
	{
		cin >> str;

		int securityNum = CapitalLettersChecker(str);

		size_t beginning = strlen(passwords[securityNum]);
		for (size_t i = beginning, j = 0; i < strlen(str) + beginning; i++, j++)
		{
			passwords[securityNum][i] = str[j];
		}

	}

	// Backward for-loop so the output is the same as the example, because no additional information for it was given, so I assume it is meant to be printed in descending order of the securityNumber at the beginning.
	for (int i = ARRAY_SIZE - 1; i >= 0; i--)
	{
		if (passwords[i][0] != 0)
		{
			cout << i;
			int index = 0;
			while (passwords[i][index] != '\0')
			{
				cout << passwords[i][index];
				index++;
			}
			cout << endl;
		}
	}

	return 0;
}