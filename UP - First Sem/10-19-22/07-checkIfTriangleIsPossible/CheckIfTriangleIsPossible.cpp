#include <iostream>
using namespace std;

int main()
{
	double side1;
	double side2;
	double side3;

	cin >> side1;
	cin >> side2;
	cin >> side3;

	if ((side1 + side2 > side3) && (side1 + side3 > side2) && (side2 + side3 > side1))
	{
		cout << "true";
	}
	else {
		cout << "false";
	}
}