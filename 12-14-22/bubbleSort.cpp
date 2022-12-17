#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int* SortArray(int* arr, int size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	// [1, 3, 2, 5, 7]
	return arr;
}

int main()
{
	cout << "Enter size of the array: ";
	int size;
	std::cin >> size;

	int* arr = new int[size];

	for (size_t i = 0; i < size; i++)
	{
		cout << "Enter element at index " << i << " : ";
		cin >> arr[i];
	}

	arr = SortArray(arr, size);

	cout << "Sorted array: ";
	cout << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}

	delete[] arr;
}