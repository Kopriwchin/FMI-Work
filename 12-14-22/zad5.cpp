#include <iostream>
using std::cout;
using std::endl;

bool isPrime(int number)
{
	bool is_prime = true;

	if (number == 0 || number == 1)
	{
		is_prime = false;
	}

	for (size_t i = 2; i <= number / 2; i++)
	{
		if (number % i == 0)
		{
			is_prime = false;
			break;
		}
	}

	return is_prime;
}

void PrintArray(int* array, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
}

int* ResizeArray(int* array, int size)
{
	int* newArray = new int[size];

	for (size_t i = 0; i < size; i++)
	{
		newArray[i] = array[i];
	}

	return newArray;
}

int* FilterPrimeNumbers(int* arr, int size)
{
	int* tempArr = new int[size];
	int j = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (isPrime(arr[i]))
		{
			tempArr[j++] = arr[i];
		}
	}

	int* result = ResizeArray(tempArr, j);

	PrintArray(result, j);

	delete[] tempArr;
	return result;
}

int main()
{
	int size = 7;

	int* arr = new int[size] {3, 5, 8, 7, 11, 24, 42};

	int* newArr = FilterPrimeNumbers(arr, size);

	delete[] newArr;
	delete[] arr;
}