#include <iostream>
using std::cout;

char* stringWithoutNumbers(char* str, int size)
{
	int newSize = 0;
	int* indexes = new int[size];
	
	for (size_t i = 0, j = 0; i < size; i++)
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			continue;
		}
		newSize++;
		indexes[j++] = i;
	}

	char* newStr = new char[newSize];

	for (size_t i = 0; i < newSize; i++)
	{
		newStr[i] = str[indexes[i]];
	}

	return newStr;
}

int main()
{
	char arr[] = "i1v2an345cho1oo";

	char* newArr = stringWithoutNumbers(arr, sizeof(arr) / sizeof(char));

	for (size_t i = 0; i < strlen(newArr); i++)
	{
		cout << newArr[i];
	}
	
	delete[] newArr;
}