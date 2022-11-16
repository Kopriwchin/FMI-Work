#include <iostream>
using namespace std;

int binaryNumber[32];

int main()
{
    int n, numberLength = 0, counter = 0;

    cout << "Enter a number: ";
    cin >> n;

    while (n != 0)
    {
        int remainder = n % 2;
        binaryNumber[numberLength] = char(remainder);
        n /= 2;
        numberLength++;
    }

    for (int i = 0; i < numberLength; i++)
    {
        if (binaryNumber[i] == 1)
        {
            counter++;
        }
    }

    cout << counter;


    return 0;
}