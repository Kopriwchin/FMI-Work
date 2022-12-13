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

	cout << endl;
}

void PrintArray(int* array, int a)
{
	for (size_t i = 0; i < a - 1; i++)
	{
		cout << array[i] << " ";
	}
	cout << array[a - 1] << "\n";
	cout << endl;
}

int* SortArrayAscending(int* array, int size) {

	int i, j;

	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}

	return array;
}

int* FindSecondaryDiagonal(int** matrix, int a) {
	int* diagonal = new int[a];

	int temp = a;

	for (size_t i = 1; i <= a; i++)
	{
		diagonal[i - 1] = matrix[temp - 1][i - 1];
		temp--;
	}

	return diagonal;
}

int** MoveColumn(int** matrix, int c, int a)
{
	// Optimisation
	if (c == a) {
		return matrix;
	}
	
	while (c > a)
	{
		c -= a;
	}
	
	int** movedMatrix = new int* [a];
	int* lastColumn = new int[a];

	for (size_t i = 0; i < c; i++)
	{
		for (int i = 0; i < a; i++)
		{
			lastColumn[i] = matrix[i][a - 1];
		}

		movedMatrix = new int* [a];
		for (size_t i = 0; i < a; i++)
		{
			movedMatrix[i] = new int[a];
			movedMatrix[i][0] = lastColumn[i];
		}

		for (size_t i = 0; i < a - 1; i++)
		{
			for (size_t j = 0; j < a; j++)
			{
				movedMatrix[j][i + 1] = matrix[j][i];
			}
		}

		matrix = movedMatrix;
	}

	delete[] lastColumn;

	return movedMatrix;
}

int** Initialize(int** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cin >> matrix[i][j];
		}
	}

	return matrix;
}

int main()
{
	int a, c;

	cin >> a;

	int** matrix = new int* [a];

	matrix = Initialize(matrix, a);

	cin >> c;

	cout << "\n";

	matrix = MoveColumn(matrix, c, a);

	cout << "New matrix after the rearrange:\n";
	PrintMatrix(matrix, a);

	int* diagonal = FindSecondaryDiagonal(matrix, a);

	cout << "Secondary diagonal:\n";
	PrintArray(diagonal, a);

	diagonal = SortArrayAscending(diagonal, a);

	cout << "Sorted secondary diagonal and final answer:\n";
	PrintArray(diagonal, a);

	for (int i = 0; i < a; i++) {
		delete[] matrix[i];
	}

	delete[] matrix;
	delete[] diagonal;
}