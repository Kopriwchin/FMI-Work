#include <iostream>

using namespace std;

int main()
{
	int array[] = {1, 2, 3, 4, 3, 2, 1};
	int length = sizeof(array) / 4;

	for (int i = 0; i < length; i++)
	{
		if (array[i] != array[length - 1 - i])
		{
			cout << "false";
			return 1;
		}
	}
	cout << "true";
	return 0;
}