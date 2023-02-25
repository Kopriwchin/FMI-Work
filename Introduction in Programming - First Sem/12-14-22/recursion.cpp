#include <iostream>
using std::cout;

int sum(int* array, int size)
{
	if (size == 0)
	{
		return 0;
	}

	return array[size - 1] + sum(array, size - 1);
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5};
	cout << sum(arr, 5);
}