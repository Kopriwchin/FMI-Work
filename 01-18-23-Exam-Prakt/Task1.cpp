#include <iostream>
#include <ctime>
#pragma warning(disable : 4996)

using std::cout;
using std::cin;
using std::endl;

long long RecursiveFormula(long long* array, long long length)
{
    if (length == 1 || length == 2)
    {
        return 1;
    }

    if (array[length] != 0)
    {
        return array[length];
    }

    return array[length] = (RecursiveFormula(array, length - 1) + RecursiveFormula(array, length / 2));
}

int main() {
    time_t curr_time;
    curr_time = time(NULL);

    tm* tm_local = localtime(&curr_time);
    cout << "Current local time : " << tm_local->tm_hour << ":" << tm_local->tm_min << ":" << tm_local->tm_sec;
    cout << "\n";

    long long length;

    cin >> length;

    if (length < 30 || length > 1000)
    {
        return -1;
    }

    long long* array = new long long[1000] {0};

    for (size_t i = 30; i <= length; i++)
    {
        cout << RecursiveFormula(array, i) % 1000000007 << endl;
    }

    delete[] array;

    cout << "\n";
    curr_time = time(NULL);
    tm_local = localtime(&curr_time);
    cout << "Current local time : " << tm_local->tm_hour << ":" << tm_local->tm_min << ":" << tm_local->tm_sec;
    cout << "\n\n\n";
    return 0;
}
