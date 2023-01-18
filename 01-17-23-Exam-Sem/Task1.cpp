#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//void PrintMatrix(int** matrix, int n, int m)
//{
//    cout << endl;
//    for (size_t i = 0; i < n; i++)
//    {
//        for (size_t j = 0; j < m; j++)
//        {
//            cout << matrix[i][j] << " ";
//        }
//        cout << endl;
//    }
//}

void SortMatrix(int**& matrix, int n, int m)
{
    for (size_t j = 0; j < m; j++)
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t k = i + 1; k < n; k++)
            {
                if (matrix[i][j] > matrix[k][j])
                {
                    int temp = matrix[i][j];
                    matrix[i][j] = matrix[k][j];
                    matrix[k][j] = temp;
                }
            }
        }
    }
}

int** InitializeMatrix(unsigned n, unsigned m)
{
    int** matrix = new int* [n];

    for (size_t i = 0; i < n; i++)
    {
        matrix[i] = new int[m];
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            cin >> matrix[i][j];
        }
    }

    return matrix;
}

void CheckForPermutation(int** matrix, int n, int m)
{
    bool anyPerms = false;
    bool isPermutation = true;

    int index = 0;

    for (index = 0; index < n; index++)
    {
        for (size_t i = 1; i < n; i++)
        {
            for (size_t j = 0; j < m; j++)
            {
                if (j == index && j == i)
                {
                    isPermutation = false;
                    break;
                }

                if (matrix[j][index] != matrix[j][i])
                {
                    isPermutation = false;
                    break;
                }
            }

            if (isPermutation)
            {
                cout << index << " " << i;
                anyPerms = true;
            }

            isPermutation = true;
        }
    }


    if (!anyPerms)
    {
        cout << "No";
    }
}

int main()
{
    unsigned n;

    unsigned  m;

    cin >> n >> m;

    int** matrix = InitializeMatrix(n, m);

    SortMatrix(matrix, n, m);

    //PrintMatrix(matrix, n, m);

    CheckForPermutation(matrix, n, m);

    delete[] matrix;
}