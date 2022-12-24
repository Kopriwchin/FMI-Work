#include <iostream>
using std::cin;
using std::cout;

bool checkIfNumbersAreAscending(int arr[], int n)
{
	if (n == 1 || n == 0)
	{
		return 1;
	}

	if (arr[n - 1] < arr[n - 2])
	{
		return 0;
	}
	return checkIfNumbersAreAscending(arr, n - 1);
}

int main()
{
	int arr[] = { 20, 23, 25, 78, 88 };

	int size = sizeof(arr) / sizeof(arr[0]);

	if (checkIfNumbersAreAscending(arr, size))
	{
		cout << "true";
	}
	else {
		cout << "false";
	}
}