#include <iostream>
using namespace std;

const int MAX_SIZE = 50;
char arr[MAX_SIZE][MAX_SIZE];

void PrintMatrix(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] != '#')
            {
                cout << ' ';
            }
            cout << arr[i][j];
        }
        cout << "\n";
    }

    cout << "\n" << "\n";
}

int main()
{
    int n;
    cin >> n;

    if (n % 2 == 0)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        arr[0][i] = '#';
        PrintMatrix(n);
    }
    for (int i = 1; i < n / 2; i++)
    {
        arr[i][n - 1] = '#';
        PrintMatrix(n);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        arr[n / 2][i] = '#';
        PrintMatrix(n);
    }
    for (int i = n / 2 + 1; i < n - 1; i++)
    {
        arr[i][0] = '#';
    }
    for (int i = 0; i < n; i++)
    {
        arr[n-1][i] = '#';
        PrintMatrix(n);
    }

    return 0;
}