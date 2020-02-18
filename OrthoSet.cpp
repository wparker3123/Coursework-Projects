#include <iostream>
#include <string>
#include <math.h>

using namespace std;
/*Postcondition: returns double dynamic array that represents the "downgrade" of the matrix or officially the cofactor.
So, if matrix 4x4, a 3x3 matrix will be returned excluding the column pointed to by the vaeriable pos */
void printSet(double** M, int n, int size)
{
	cout << "Entered Vectors: " << endl;
	for (int a = 0; a < n; a++)
	{
		cout << "	v" << a << ": { ";
		for (int b = 0; b < size; b++)
		{
			if (b != size - 1)
				cout << M[a][b] << ", ";
			else
				cout << M[a][b];
		}
		cout << " }" << endl;
	}
}
double dotProduct(double* a1, double* a2, int n)
{
	double dot = 0;
	for (int c = 0; c < n; c++)
	{
		dot += a1[c] * a2[c];
	}

	return dot;

}
void subtract(double*& s1, double* s2, int size)
{
	for (int a = 0; a < size; a++)
	{
		s1[a] -= s2[a];
	}
}
void scalarMultiply(double x, double*& s1, int size)
{
	for (int a = 0; a < size; a++)
	{
		s1[a] *= x;
	}
}
double** downgrade(int pos, double** M, int n)
{
	double** M1 = new double*[n - 1];
	for (int i = 0; i < n - 1; i++)
		M1[i] = new double[n - 1];

	int column = 0;
	int c;
	int r = 0;
	for (int row = 1; row < n; row++)
	{
		c = 0;
		for (int column = 0; column < n; column++)
		{
			if (column != pos)
			{
				M1[r][c] = M[row][column];
				c++;
			}
		}
		r++;
	}

	return M1;
}

//Postcondition: returns double number representing the determinant of the matrix.
double determinant(double** M, int n)
{
	//2x2 Matrix
	double det = 0;
	if (n == 1) //1 x 1 Matrix
	{
		det += M[0][0];
	}

	else if (n == 2) //2 x 2 Matrix
	{
		det += M[0][0] * M[1][1];
		det -= M[0][1] * M[1][0];
	}
	else if (n == 3)//3 x 3 Matrix
	{

		det += M[0][0] * determinant(downgrade(0, M, n), n - 1);
		det -= M[0][1] * determinant(downgrade(1, M, n), n - 1);
		det += M[0][2] * determinant(downgrade(2, M, n), n - 1);
	}
	else//n x n Matrix
	{
		for (int a = 0; a < n; a++)
		{
			det += pow(-1.0, a) * (M[0][a] * determinant(downgrade(a, M, n), n - 1));
		}
	}

	return det;

}
void printMatrix(double** M, int n, int size)
{
	for (int row = 0; row < size; row++)
	{
		cout << "	| ";
		for (int column = 0; column < n; column++)
		{
			cout << M[row][column] << " ";
		}
		cout << "|" << endl;
	}
	cout << endl;
}

bool checkSet(double** M, int n, int size)
{
	if (size == n && determinant(M,n) != 0)
		return true;
	

}

double** grammProcess(double** M, int size, int n)
{
	double** orthoSet = new double*[n];
	for (int i = 0; i < n; i++)
		orthoSet[i] = new double[size];

	
	for (int a = 0; a < n; a++)
	{
		for (int c = 0; c < size; c++)
		{
			if (a < 1)
				orthoSet[a][c] = M[a][c];
			else
			{
				orthoSet[]
				subtract(orthoSet[a - 1], scalarMultiply((dotProduct(M[a], orthoSet[a - 1], size) / dotProduct(orthoSet[a - 1], orthoSet[a - 1], size), orthoSet[a - 1], size);
			}
		}
	}


}
int main()
{
	cout << "Enter n or vector size(for R^n):	";
	int size;
	cin >> size;
	cout << "Enter number of vectors in set:  ";
	int n;
	cin >> n;

	double** vectorSet = new double*[n];
	for (int i = 0; i < n; i++)
		vectorSet[i] = new double[size];

	double** matrix = new double*[size];
	for (int x = 0; x < size; x++)
		matrix[x] = new double[n];
	
	cout << "Enter " << n << " linearly INDEPENDENT vectors of size " << size << ":  ";
	for (int a = 0; a < n; a++)
	{
		
		for (int b = 0; b < size; b++)
		{
			double temp;
			cin >> temp;
			vectorSet[a][b] = temp;
			matrix[b][a] = temp;
		}

	}

	printSet(vectorSet, n, size);

	//printMatrix(matrix, n, size);

	system("pause");

	delete vectorSet;
	delete matrix;
	return 0;
}