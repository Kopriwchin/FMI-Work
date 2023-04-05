#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

void WriteFile() {
	std::ofstream writeNumbers("numbers.dat", std::ios::binary);

	if (!writeNumbers || !writeNumbers.is_open())
	{
		cout << "Error! Could not open the requested file for writing!" << endl;
		return;
	}

    cout << "Enter -1 to end" << endl;
    cout << "Enter numbers, seperated by space: ";

	int number;

	cin >> number;

	while (number != -1)
	{
		writeNumbers.write(reinterpret_cast<const char*>(&number), sizeof(int));
		cin >> number;
	}
}

int GetBiggestNumber() {
	std::ifstream numbersFile("numbers.dat", std::ios::binary);

	if (!numbersFile.is_open() || !numbersFile)
	{
		cout << "Error! Could not open the requested file for reading!" << endl;
		return -1;
	}

	int biggestNum = INT_LEAST32_MIN;

	int numForReading;

	while (!numbersFile.eof())
	{
		numbersFile.read(reinterpret_cast<char*>(&numForReading), sizeof(int));
		if (numForReading > biggestNum)
			biggestNum = numForReading;
	}

	return biggestNum;
}

int main()
{
	WriteFile();
	 
	cout << GetBiggestNumber();
}