#include <iostream>
using std::cin;
using std::cout;

bool doesContainNumber(int number, int searchedNum)
{
	if (number == 0)
		return false;

	if (number % 10 == searchedNum)
		return true;

	return doesContainNumber(number /= 10, searchedNum);
}


bool validateInput(int number, int searchedNum)
{
	if (number == 0 && searchedNum == 0)
	{
		return true;
	}

	doesContainNumber(number, searchedNum);
}

int main()
{
	const char* output = validateInput(1234, 2) ? "true" : "false";

	cout << output;
}