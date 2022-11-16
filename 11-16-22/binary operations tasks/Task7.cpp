#include <iostream>
using namespace std;

int arr[] = { 9, 18, 9, 12, 18, 15, 12 };

int getUniqueNumber(int arr[], int length)
{
    int result = 0;
    for (int i = 0; i < length; i++)
    {
        result ^= arr[i];
    }

    return result;
}

int main()
{
    int arr[] = { 9, 18, 9, 12, 18, 15, 12 };
    int arrayLength = *(&arr + 1) - arr;

    int uniqueNumber = getUniqueNumber(arr, arrayLength);
    cout << uniqueNumber;

    return 0;
}