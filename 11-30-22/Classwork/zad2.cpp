#include <iostream>
using namespace std;

char* substringFunc(char* word, int start, int end) {
	int i, j;
	int size = (end - start);

	if (size < 0)
	{
		size *= -1;
		int temp = start;
		start = end;
		end = temp;
	}

	char* newWord = new char[size + 1];

	for (i = 0, j = start; j <= end; i++, j++)
	{
		newWord[i] = word[j];
	}
	newWord[i] = '\0';

	return newWord;
}

int main()
{
	char word[100] = "Hello";

	int start, end;

	cin >> start;
	cin >> end;

	const char* newWord = substringFunc(word, start, end);

	cout << newWord;
}