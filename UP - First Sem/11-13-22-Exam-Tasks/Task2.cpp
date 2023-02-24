#include <iostream>

using namespace std;

bool isPrime(int number)
{
	for (int i = 2; i <= number - 1; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}

	return true;
}

int main()
{
	int n;
	int lastNum;

	cin >> n;

	for (int i = 2; n != 1; i++)
	{
		lastNum = i;

		if (isPrime(i))
		{
			if (n % i == 0)
			{
				n /= i;
				if (n == 1)
				{
					cout << i;
					return 0;
				}
				cout << i << ".";
				i--;
			}
		}
	}
}