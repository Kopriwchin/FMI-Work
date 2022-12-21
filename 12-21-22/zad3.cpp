#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int outputReverseNumber(int num)
{
	if (num / 10 == 0)
	{
		return num % 10;
	}
	cout << num % 10;

	return outputReverseNumber(num / 10);
}

int main()
{
	int n;
	cout << "Enter number: ";
	cin >> n;
	cout << outputReverseNumber(n) << endl;
}