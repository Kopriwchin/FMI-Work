#include <iostream>

using namespace std;

int reverseNum(int number)
{
	int n = number;
	int reversedNum = 0;
	int remainder = 0;

	while (n > 0)
	{
		remainder = n % 10;
		reversedNum = reversedNum * 10 + remainder;
		n /= 10;
	}
	return reversedNum;
}

bool isDoublePalindrome(int number)
{
	if (number == reverseNum(number) && (number*number) == reverseNum(number*number))
	{
		return true;
	}
	return false;
}

int main()
{
	int k;

	cin >> k;

	if (k <= 0)
	{
		return 0;
	}

	int counter = 0;

	for (int i = 11; i < INT32_MAX; i++)
	{
		if (isDoublePalindrome(i))
		{
			cout << i << " " << (i * i) << "\n";
			counter++;
			if (k == counter)
				break;
		}
	}
	return 0;
}