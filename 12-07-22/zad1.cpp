#include <iostream>
using namespace std;

void PrintMatrix(int** matrix, int a)
{
	for (size_t i = 0; i < a; i++)
	{
		for (size_t j = 0; j < a; j++)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << '\n';
	}
}

int** MoveColumn(int** matrix, int c, int a)
{
	int* lastColumn = new int[a];
	
	for (int i = 0; i < a; i++)
	{
		lastColumn[i] = matrix[i][a - 1];
	}

	for (size_t i = 0; i < a - 1; i++)
	{
		for (size_t j = 0; j < a; j++)
		{
			int temp_array = matrix[j][1];
			matrix[j][1] = matrix[j][a - 1];
			matrix[j][a - 1] = temp_array;
		}
	}
	

	PrintMatrix(matrix, a);

	return matrix;
}

int main()
{
	int a;
	int c;

	cin >> a;

	int** matrix = new int* [a];

	for (int i = 0; i < a; i++)
	{
		matrix[i] = new int[a];
	}

	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < a; j++)
		{
			cin >> matrix[i][j];
		}
	}

	cin >> c;

	cout << '\n';

	MoveColumn(matrix, c, a);

	for (int i = 0; i < a; i++) {
		delete[] matrix[i];
	}

	delete[] matrix;
}