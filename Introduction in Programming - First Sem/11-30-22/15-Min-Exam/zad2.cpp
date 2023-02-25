#include <iostream>
using namespace std;

int main()
{
	int arr[3][3];
	int sum = 0;

	for (int i = 0; i < 3; i++)
	{
		cout << "Print row " << i + 1 << endl;

		for (int j = 0; j < 3; j++)
		{
			cin >> arr[i][j];
			sum += arr[i][j];
		}
	}

	cout << sum;

    return 0;
}