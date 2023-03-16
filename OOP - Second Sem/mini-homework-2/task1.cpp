#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	const char FILE_NAME[] = "printOwnCodeProgram.cpp";
	const short BUFFER_SIZE = 1024;
	const char INVALID_FILE_MSG[] = "Error! Could not open requested file!";

	std::ifstream file(FILE_NAME);

	if (!file.is_open())
	{
		cout << INVALID_FILE_MSG;
		return -1;
	}

	while (!file.eof())
	{
		char buffer[BUFFER_SIZE];
		file.getline(buffer, BUFFER_SIZE);
		cout << buffer << endl;
	}

	file.close();
	return 0;
}