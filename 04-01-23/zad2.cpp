#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int BinarySearchFindElementInSortedArray(int value, int* array, int max)
{
    if (max == 0)
        return -1;

    int middle = max / 2;

    if (array[middle] == value)
        return middle;

    bool lower = value < array[middle];
    int n = lower ? BinarySearchFindElementInSortedArray(value, array, middle)
        : BinarySearchFindElementInSortedArray(value, array + middle + 1, max - middle - 1);

    return n != -1 && !lower ? n + middle + 1 : n;
}

int main()
{
    int const n = 7;
    int value1 = 4;
    int value2 = 13;
    int value3 = 22;

    int array[n] = { 3,4,9,13,13,17,22 };

    cout << value1 << " = " << BinarySearchFindElementInSortedArray(value1, array, n) << endl;
    cout << value2 << " = " << BinarySearchFindElementInSortedArray(value2, array, n) << endl;
    cout << value3 << " = " << BinarySearchFindElementInSortedArray(value3, array, n) << endl;
    return 0;
}