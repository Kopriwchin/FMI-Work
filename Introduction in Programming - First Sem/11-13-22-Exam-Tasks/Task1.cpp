#include <iostream>

using namespace std;

int main() 
{
	int n;

	cin >> n;

	int counter = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			counter++;
			cout << i << " ";

			if (counter == n)
				return 0;
		}
	}

	return 0;
}