#include <iostream>
using namespace std;

int main()
{
	double num;

	cin >> num;

	if (num <= 10)
	{
		cout << "slow";
	}
	else if (num > 10 && num <= 50)
	{
		cout << "average";
	}
	else if (num > 50 && num < 150)
	{
		cout << "fast";
	}
	else {
		cout << "extremely fast";
	}
}