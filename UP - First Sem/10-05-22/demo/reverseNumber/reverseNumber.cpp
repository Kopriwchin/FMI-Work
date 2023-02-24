#include <iostream>
using namespace std;

int main()
{
    int number = 0;
    int sum = 0;

    cin >> number;

    sum += number % 10 * 100;
    number /= 10;
    sum += number % 10 * 10;
    number /= 10;
    sum += number % 10;
    number /= 10;

    cout << sum + 1;

    return 0;
}
