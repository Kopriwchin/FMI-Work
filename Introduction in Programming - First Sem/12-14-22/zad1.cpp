#include <iostream>
using std::cout;

int* insertAt(int index, int element, int* arr, int size)
{
	int* newArray = new int[size + 1];

	for (size_t i = 0; i < index; i++)
	{
		newArray[i] = arr[i];
	}
	newArray[index] = element;

	for (size_t i = index; i < size; i++)
	{
		newArray[i + 1] = arr[i];
	}
	
	return newArray;
}

int main()
{
	int arr[] = {1, 2, 3, 4};
	int* result = insertAt(2, 999, arr, 4);

	for (size_t i = 0; i < sizeof(arr) / sizeof(int) + 1; i++)
	{
		cout << result[i] << " ";
	}

	delete[] result;
	return 0;
}