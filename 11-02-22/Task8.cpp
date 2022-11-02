#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int dollarSigns = 1;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < dollarSigns; j++)
		{
			cout << "$ ";
		}
		dollarSigns++;
		cout << "\n";
	}
}