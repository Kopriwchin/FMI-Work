#include <iostream>
using std::cout;

int* removeAt(int* arr, int index, int size)
{
	int* newArr = new int[size - 1];

	for (size_t i = 0, j = 0; i < size; i++)
	{
		if (i == index)
		{
			continue;
		}
		newArr[j] = arr[i];
		j++;
	}

	return newArr;
}

int main()
{
	int arr[] = { 1, 2, 3, 4, 5 };

	int* intArr = removeAt(arr, 3, 5);

	for (size_t i = 0; i < sizeof(arr) / sizeof(int) - 1; i++)
	{
		cout << intArr[i] << " ";
	}

	delete[] intArr;
}