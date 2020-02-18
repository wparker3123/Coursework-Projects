#include <iostream>
#include <string>
#include <math.h>

using namespace std;

//Postcondition: Prints Matrix M on line.
void printMatrix(double** M, int n)
{
	for (int q = 0; q < n; q++)
	{
		cout << "	| ";
		for (int p = 0; p < n; p++)
		{
			cout << M[q][p] << " ";
		}
		cout << "|" << endl;
	}
	cout << endl;
}

/*Postcondition: returns double dynamic array that represents the "downgrade" of the matrix or officially the cofactor. 
So, if matrix 4x4, a 3x3 matrix will be returned excluding the column pointed to by the vaeriable pos */
double** downgrade(int pos, double** M, int n)
{
	double** M1 = new double*[n - 1];
	for (int i = 0; i < n-1; i++)
		M1[i] = new double[n-1];

	int column = 0;
	int c;
	int r = 0;
	for (int row = 1; row < n; row++)
	{
		c = 0;
		for(int column = 0; column < n; column++)
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
int main()
{
	//Make Matrix using n
	cout << "Enter n to build an n x n matrix" << endl;
	int n = 0;
	cin >> n;

	double** Matrix = new double*[n];
	for (int i = 0; i < n; i++)
		Matrix[i] = new double[n];
	
	for (int q = 0; q < n; q++)
	{
		for (int p = 0; p < n; p++)
		{
			cin >> Matrix[q][p];
		}
	}
	cout << "\nEntered Matrix: \n" << endl;
	printMatrix(Matrix, n);
	cout << "Determinant: " << determinant(Matrix, n) << endl;
	

	for (int i = 0; i < n; ++i) {
		delete[] Matrix[i];
	}
	delete[] Matrix;
	system("pause");

	return 0;
}