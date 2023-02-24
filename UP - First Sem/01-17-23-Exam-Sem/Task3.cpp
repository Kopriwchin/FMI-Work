#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void PrintBinary(long n, int length)
{
    long i;
    cout << '0';
    for (i = 1 << length; i > 0; i = i / 2)
    {
        if ((n & i) != 0)
        {
            cout << '1';
        }
        else
        {
            cout << '0';
        }
    }
}

int BinaryToDecimal(long long n) {
    int ans = 0;
    int remainder = 0;
    int i = 0;

    while (n != 0) {
        remainder = n % 10;
        ans += remainder * pow(2, i);
        i++;

        n = n / 10;
    }

    return ans;
}

int RecursiveFunc(int k, int n, int* prices, int index)
{
	if (k > *prices)
	{
        PrintBinary(BinaryToDecimal(index), n);
        cout << endl;
	}
    
    if (index == n - 1)
    {
        return 0;
    }
    return RecursiveFunc(k, n, prices + 1, index + 1);
}



int main()
{
	int k;
	int n;
	cin >> k >> n;
    int* prices = new int[n];

    for (size_t i = 0; i < n; i++)
    {
        cin >> prices[i];
    }

    int index = 0;

    RecursiveFunc(k, n, prices, index);
}