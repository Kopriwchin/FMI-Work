#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void SortArray(int*& arr, int size)
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
}

int* MergeTwoArrays(int* firstArr, int* secondArr, int firstArraySize, int secondArraySize)
{
	int* result = new int[firstArraySize + secondArraySize];

	for (size_t i = 0; i < firstArraySize; i++)
	{
		result[i] = firstArr[i];
	}

	for (size_t i = 0; i < secondArraySize; i++)
	{
		result[i + firstArraySize] = secondArr[i];
	}

	SortArray(result, firstArraySize + secondArraySize);

	return result;
}

int main()
{
	cout << "Enter size of the first array: ";
	int firstSize;
	cin >> firstSize;

	int* firstArr = new int[firstSize];

	for (size_t i = 0; i < firstSize; i++)
	{
		cin >> firstArr[i];
	}
	cout << endl;

	cout << "Enter size of the second array: ";
	int secondSize;
	cin >> secondSize;

	int* secondArr = new int[secondSize];

	for (size_t i = 0; i < secondSize; i++)
	{
		cin >> secondArr[i];
	}
	cout << endl;

	int* result = MergeTwoArrays(firstArr, secondArr, firstSize, secondSize);

	for (size_t i = 0; i < firstSize + secondSize; i++)
	{
		cout << result[i] << " ";
	}
	cout << endl;

	delete[] firstArr;
	delete[] secondArr;
}