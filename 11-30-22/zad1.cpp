#include <iostream>
using namespace std;

int CountNumbers(int n) {
	int count = 0;

	while (n != 0) {
		n /= 10;
		count++;
	}

	return count;
}

int main()
{
	int n = 0;;
	int sum = 0;
	

	for (int i = 0; i < 5; i++)
	{
		cin >> n;

		if (n < 0 || n > 5000)
		{
			cout << "Integer must be in the interval [0..5000]";
			return -1;
		}

		sum += n;
	}

	cout << CountNumbers(sum);
	return 0;
}