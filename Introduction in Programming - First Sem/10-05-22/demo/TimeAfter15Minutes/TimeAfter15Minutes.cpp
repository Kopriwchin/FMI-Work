#include <iostream>

using namespace std;

int main()
{
    int hours;
    cin >> hours;
    int minutes;
    cin >> minutes;

    if ((hours < 0 || hours > 23) || (minutes < 0 || minutes > 59))
    {
        cout << "Invalid input";
        return 1;
    }

    if (minutes + 15 == 60)
    {
        hours++;
        minutes = 0;
    }
    else if (minutes + 15 > 60)
    {
        hours++;
        minutes -= 45;
    }
    else {
        minutes += 15;
    }

    if (hours < 10)
    {
        if (minutes < 10)
        {
            cout << "0" << hours << ":" << "0" << minutes;
        }
        else {
            cout << "0" << hours << ":" << minutes;
        }
    }
    else if (minutes < 10) 
    {
        cout << hours << ":" << "0" << minutes;
    }
    else if (hours == 24)
    {
        cout << "00:" << minutes;
    }
    else
    {
        cout << hours << ":" << minutes;
    }
}