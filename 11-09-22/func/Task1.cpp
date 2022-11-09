#include <iostream>
using namespace std;

int returnModule(int n)
{
	if (n < 0)
	{
		cout << (n * -1);
	}
	else {
		cout << n;
	}

	return 0;
}

int main() {
	int n;

	cin >> n;

	int var = returnModule(n);
}