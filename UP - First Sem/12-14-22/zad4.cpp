#include <iostream>
using std::cout;
using std::endl;

char* ResizeString(char* str, int size)
{
	char* newArr = new char[size];
	int i = 0;

	for (i = 0; i < size; i++)
	{
		newArr[i] = str[i];
	}

	return newArr;
}

char* ExtractUppercase(char* str)
{
	char* newWord = new char[strlen(str)];
	int size = 0;

	for (size_t i = 0, j = 0; i < strlen(str); i++)
	{
		if (str[i] >= 65 && str[i] < 90)
		{
			newWord[j++] = str[i];
			size++;
		}
	}

	char* result = ResizeString(newWord, size);
	delete[] newWord;

	return result;
}

char* ExtractLowercase(char* str)
{
	char* newWord = new char[strlen(str)];
	int size = 0;

	for (size_t i = 0, j = 0; i < strlen(str); i++)
	{
		if (str[i] >= 97 && str[i] < 122)
		{
			newWord[j++] = str[i];
			size++;
		}
	}

	char* result = ResizeString(newWord, size);
	delete[] newWord;

	return result;
}

int main()
{
	char word[] = "I am the best Player";

	//char* newWord = ExtractUppercase(word);
	//
	//for (size_t i = 0; newWord[i] > 0; i++)
	//{
	//	cout << newWord[i];
	//}

	//delete newWord;


	/*char* newWord = ExtractLowercase(word);

	for (size_t i = 0; newWord[i] > 0; i++)
	{
		cout << newWord[i];
	}

	delete newWord;*/
}