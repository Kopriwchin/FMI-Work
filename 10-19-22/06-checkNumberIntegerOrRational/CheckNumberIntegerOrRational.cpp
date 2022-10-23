#include <iostream>
using namespace std;

int main()
{
	int number;

	cin >> number;

	int firstNum = number % 10;
	int secondNum = number / 10 % 10;
	int thirdNum = number / 100;

	if (firstNum == secondNum)
	{
		cout << "true";
	}
	else if (firstNum == thirdNum) {
		cout << "true";
	}
	else if (secondNum == thirdNum) {
		cout << "true";
	}
	else {
		cout << "false";
	}

	return 0;
}