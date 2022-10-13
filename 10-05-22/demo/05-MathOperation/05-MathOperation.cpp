#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int a, b;

    cin >> a;
    cin >> b;

    int firstCalc = pow(a + b, 4);
    int secondCalc = pow(a - b, 2);

    int result = firstCalc - secondCalc;
    cout << result;

    return 0;
}