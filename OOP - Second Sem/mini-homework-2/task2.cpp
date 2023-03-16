#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

const char READ_FILE_NAME[] = "input.txt";
const char WRITE_FILE_NAME[] = "output.txt";
const size_t BUFFER_SIZE = 1024;

void PrintErrorMessage(const char filename[])
{
	cout << "Error! Could not open the requested file: " << filename << endl;
}

int main()
{
	std::ifstream inputFile(READ_FILE_NAME);

	if (!inputFile.is_open())
	{
		PrintErrorMessage(READ_FILE_NAME);
		return -1;
	}

	std::ofstream outputFile(WRITE_FILE_NAME);
	if (!outputFile.is_open())
	{
		PrintErrorMessage(WRITE_FILE_NAME);
		return -1;
	}

	while (!inputFile.eof())
	{
		char buffer[BUFFER_SIZE];
		inputFile.getline(buffer, BUFFER_SIZE);
		
		int i = 0;
		int j;

		int lineLength = strlen(buffer);

		for (i = lineLength - 1, j = 0; i >= 0; i--, j++)
		{
			outputFile << buffer[i];
		}
		outputFile << '\n';

	}

	inputFile.close();
	outputFile.close();
}