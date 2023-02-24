#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int findPowerOfNumber(int n, int pow)
{
	if (pow == 0)
	{
		return 1;
	}

	if (pow & 1 == 0)
	{
		int fastCalc = findPowerOfNumber(n, pow / 2);

		return fastCalc * fastCalc;
	}

	return n * findPowerOfNumber(n, pow - 1);
}

int main()
{
	int number, power;

	cout << "Enter number: ";
	cin >> number;
	cout << endl;
	cout << "Enter power: ";
	cin >> power;
	cout << endl;
	cout << "Output: " << findPowerOfNumber(number, power);
}