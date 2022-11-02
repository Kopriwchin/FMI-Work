#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int spacing = n;

	for (int i = 1; i <= n; i++)
	{
		for (int k = 0; k < spacing - 1; k++)
		{
			cout << " ";
		}
		for (int j = i; j > 0; j--)
		{
			cout << j;
		}
		spacing--;
		cout << "\n";
	}

	spacing = 1;

	for (int i = n; i > 0; i--)
	{
		for (int k = 0; k < spacing; k++)
		{
			cout << " ";
		}

		spacing++;
		
		for (int j = i - 1; j > 0; j--)
		{
			cout << j;
		}
		cout << "\n";
	}
}