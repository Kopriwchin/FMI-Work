#include <iostream>

using namespace std;

int main()
{
	int n;
	int longestStreak = 0;
	int longestNum = 0;
	int currentStreak = 1;
	cin >> n;

	while (n > 0) {
		int currentNum = n % 10;
		n /= 10;

		if (currentNum == (n % 10))
		{
			currentStreak++;
		}
		else {
			if (currentStreak > longestStreak)
			{
				longestStreak = currentStreak;
				longestNum = currentNum;
				currentStreak = 1;
			}
		}
	}

	cout << longestStreak << " (" << longestNum << ")";
}