#include <iostream>
using namespace std;

int main(int x) 
{
	int num1, num2, num3, num4, num5;

	cin >> num1 >> num2 >> num3 >> num4 >> num5;

	for (int x = -100; x <= 100; x++)
	{
		int palindrome = num1 * (x * x * x * x)
			+ num2 * (x * x * x)
			+ num3 * (x * x)
			+ num4 * x
			+ num5;

		if (palindrome >= -100 && palindrome <= 100)
		{
			if (x >= 0)
			{
				cout << x;
				cout << "\n";
			}
		}
	}
}