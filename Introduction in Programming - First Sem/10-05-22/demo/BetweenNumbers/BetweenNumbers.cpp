// BetweenNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
using namespace std;

int main()
{
    int num = 0;
    cin >> num;

	if (num < 100)
	{
		cout << "Less than 100";
	}
	else if (num >= 100 && num <= 200) {
		cout << "Between 100 and 200";
	} 
	else {
		cout << "Greater than 200";
	}
}