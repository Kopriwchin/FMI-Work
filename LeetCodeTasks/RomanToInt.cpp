#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int romanToInt(string input) {
    int result = 0;
    int number = 0;
    int previous = 0;

    for (int i = input.length() - 1; i >= 0; i--) {
        switch(input[i])
        {
            case 'I':
                number = 1;
                break;
            case 'V':
                number = 5;
                break;
            case 'X':
                number = 10;
                break;
            case 'L':
                number = 50;
                break;
            case 'C':
                number = 100;
                break;
            case 'D':
                number = 500;
                break;
            case 'M':
                number = 1000;
                break;
        }

        if (previous > number)
        {
            result -= number;
        }
        else {
            result += number;
        }

        previous = number;
    }

    return result;
}

int main()
{
    cout << romanToInt("MCMXCIV") << endl;
    cout << romanToInt("LVIII") << endl;
    cout << romanToInt("III") << endl;
}