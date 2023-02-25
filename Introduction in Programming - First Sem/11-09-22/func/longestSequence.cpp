#include <iostream>
#include <math.h>
using namespace std;

int findLength(int n)
{
	int clone = n;
	int counter = 0;

	while (clone != 0)
	{
		counter++;

		clone /= 10;
	}

	return counter;
}

int main()
{
	int n;

	cin >> n;

	int numberLength = findLength(n);

	int sequenceLength = 1;
	int longestNumber = 0;
	int longestStreak = 0;

	for (int i = 0; i < numberLength; i++)
	{
		int currentNumber = n % 10;
		n /= 10;

		if (currentNumber == (n % 10))
		{
			sequenceLength++;
		}
		else
		{
			if (sequenceLength > longestStreak)
			{
				longestStreak = sequenceLength;
				longestNumber = currentNumber;
				sequenceLength = 1;
			}
		}
	}

	cout << longestStreak << "(" << longestNumber << ")";
}