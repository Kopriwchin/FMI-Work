#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void Swap(int& num1, int& num2)
{
	int temp = num2;
	num2 = num1;
	num1 = temp;
}

int OneTimeFound(int* array, int length)
{
	int result = array[0];

	for (size_t i = 1; i < length; i++)
	{
		result ^= array[i];
	}

	return result;
}

void BubbleSort(int*& array, int length)
{
	bool swapped = false;
	size_t j = 0;

	for (size_t i = 0; i < length; i++)
	{
		for (j = 0; j < length - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				Swap(array[j], array[j + 1]);
				swapped = true;
			}
		}
		if (!swapped)
		{
			return;
		}
		j--;
	}
}


int main() {
	int length;
	cin >> length;

	int* arr = new int[length];

	for (size_t i = 0; i < length; i++)
	{
		cin >> arr[i];
	}

	if (length % 2 == 0)
	{
		BubbleSort(arr, length);

		for (size_t i = 0; i < length; i++)
		{
			cout << arr[i] << " ";
		}
	}
	else
	{
		cout << OneTimeFound(arr, length);
	}

	delete[] arr;
	return 0;
}