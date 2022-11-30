#include <iostream>
using namespace std;

int myStrLen(char word[]) {

	int index = 0;

	while (true)
	{
		if (word[index] == '\0')
		{
			return index;
		}

		index++;
	}
}

int main()
{
	char array[] = {'1', '2', '\0'};
	cout << myStrLen(array);

	// 2
}