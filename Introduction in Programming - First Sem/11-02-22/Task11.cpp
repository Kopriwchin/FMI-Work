#include <iostream>

using namespace std;

int main()
{
    int s;
    cin >> s;
    int counter = 1;
    for (size_t i = 1; i <= s; i++)
    {
        if (i % 2 != 0)
        {//123
            for (size_t j = 0; j < s; j++, counter++)
            {
                cout << counter << " ";
            }
            cout << endl;
        }
        else {
            int counter2 = counter + s - 1;
            for (size_t j = 0; j < s; j++, counter++, counter2--)
            {
                cout << counter2 << " ";
            }
            cout << endl;
        }
    }
}