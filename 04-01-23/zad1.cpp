#include <iostream>
using namespace std;

int convert(int num, int a, int b)
{
    if (num > 0)
    {
        int res = convert(num / 10, a, b);
        int t = num % 10;
        res *= 10;
        t = t == a ? b : t;
        res += t;
        return res;
    }
    return 0;
}

int main()
{
    int number = 123;
    int searchNumber = 1;
    int replaceNumber = 3;

    int result = convert(number, searchNumber, replaceNumber);

    cout << result;
    return 0;
}