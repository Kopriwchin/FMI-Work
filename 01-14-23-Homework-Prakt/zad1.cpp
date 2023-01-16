#include <iostream>
using std::cin;
using std::cout;

bool recursiveHacksaw(int size, int* sequence, bool isFirstSignLess, int index)
{
    if (sequence[index] == sequence[size - 1])
    {
        return true;
    }

    if (isFirstSignLess)
    {
        if (sequence[index] < sequence[index + 1])
        {
            return recursiveHacksaw(size, sequence, false, index + 1);
        }

        else
            return false;
    }
    else
    {
        if (sequence[index] > sequence[index + 1])
        {
            return recursiveHacksaw(size, sequence, true, index + 1);
        }

        else
            return false;
    }
}

int main()
{
    int input, index = 0;

    if (!(cin >> input) || input < 3 || 1000 < input)
    {
        cout << -1;
        return -1;
    }

    int* sequence = new int[input];

    for (size_t i = 0; i < input; i++)
    {
        if (!(cin >> sequence[i]))
        {
            cout << -1;
            return -1;
        }
    }

    bool isFirstSignLess = sequence[0] > sequence[1] ? false : true;

    recursiveHacksaw(input, sequence, isFirstSignLess, index) ? cout << "yes" : cout << "no";

    delete[] sequence;
    return 0;
}