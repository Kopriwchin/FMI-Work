#include <iostream>
using std::cin;
using std::cout;

int calculateQuincyProfit(int n, int* pricesForEachDay)
{
	int profit = 0;

	for (int i = 0; i < n; i++)
	{
		if (pricesForEachDay[i + 1] > pricesForEachDay[i])
		{
			profit += pricesForEachDay[i + 1] - pricesForEachDay[i];
		}
	}

	return profit;
}

int main()
{
	int input;

	if (!(cin >> input) || input < 0 )
	{
		return -1;
	}

	int* pricesForEachDay = new int[input];

	for (size_t i = 0; i < input; i++)
	{
		if (!(cin >> pricesForEachDay[i]) || pricesForEachDay[i] < 0)
		{
			delete[] pricesForEachDay;
			return -1;
		}
	}

	cout << calculateQuincyProfit(input, pricesForEachDay);

	delete[] pricesForEachDay;
}