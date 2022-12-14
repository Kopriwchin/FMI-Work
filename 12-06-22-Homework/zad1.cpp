#include <iostream>
using namespace std;

int digitsNumber(int arr[])
{
	int count = 0;

	while (arr[count] == 0 || arr[count] == 1)
	{
		count++;
	}

	return count;
};

int* decimalToBinary(unsigned n)
{
	int* reversedBinary = new int[8];
	int index = 0;

	while (n != 0)
	{
		reversedBinary[index] = n % 2;
		n /= 2;
		index++;
	}

	int* binaryNumber = new int[index];

	for (int i = 0; i < index; i++)
	{
		binaryNumber[i] = reversedBinary[index - 1 - i];
	}

	delete[] reversedBinary;

	return binaryNumber;
}

bool hasAlternatingBits(unsigned n)
{
	if (n >= 0 && n <= 2)
	{
		return true;
	}

	int* binaryNum = decimalToBinary(n);

	for (int i = 0; i < digitsNumber(binaryNum) - 1; i++)
	{
		if (binaryNum[i] == binaryNum[i + 1])
		{
			return false;
		}
	}

	delete[] binaryNum;

	return true;
}

int main()
{
	int input;
	cin >> input;

	if (!cin || input < 0 || input > 255)
	{
		return -1;
	}

	bool output = hasAlternatingBits(input);

	if (output)
	{
		cout << "true";
	}
	else
	{
		cout << "false";
	}

	return 0;
}