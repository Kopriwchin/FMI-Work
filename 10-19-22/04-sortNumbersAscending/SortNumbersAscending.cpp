#include <iostream>
using namespace std;

int main()
{
	int num1, num2, num3;

	cin >> num1;
	cin >> num2;
	cin >> num3;

	if (num1 > num2)
	{
		if (num2 > num3)
		{
			cout << num3;
			cout << num2;
			cout << num1;
		}
		else {
			cout << num2;
			cout << num3;
			cout << num1;
		}
	}
	else if (num2 > num1) {
		if (num1 > num3)
		{
			cout << num3;
			cout << num1;
			cout << num2;
		}
		else {
			cout << num1;
			cout << num3;
			cout << num2;
		}
	}

	return 0;
}