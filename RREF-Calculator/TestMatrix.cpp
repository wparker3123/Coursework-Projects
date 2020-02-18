#include <iostream>
#include "matrix.h"

using namespace std;
//Check if collumn has all zeroes

struct freeVar
{
	int x;
	char l;
};
void displaySolution(Matrix M, int pivots)
{
	string* solutionSet = new string[3];
	char vars[3] = { 'a', 'b', 'c' };
	int track = 0;
	if (pivots == 3) //unique solution
	{
		for (int a = 1; a <= 3; a++)
		{
			solutionSet[a - 1] = 'X' + char(a) + '=' + M.selectRow(a)[3];
		}
	}
	if (pivots < 3 && M.selectRow(3)[2] == 0)
	{
	//	int* freeColumn[3] = M.selectRow();
		if (M.selectRow(3)[2] == M.selectRow(3)[3])
		{
			for (int a = 3; a >= 1; a--)
			{
				if(M.hasPivot(a))
					solutionSet[a - 1] = 'X' + char(a) + '=' + M.selectRow(a)[3];
			}
		}
		for (int a = 0; a < 3; a++)
		{
			if (solutionSet[a] == "")
			{
				solutionSet[a - 1] = vars[track];
				track++;
			}
		}
	}
	//if() //no solution
}
bool isIdentity(Matrix a)
{
	Matrix i;
	i.makeIdentityMatrix();

	return  a == i;
}
void solveMatrix(Matrix& M)
{
	Matrix curr = M;
	int column = 0;
	int row = 1;
	int pivnum = 0;
	int pivot = 1; // represents the current pivot not total

	/*debug variables*/
	

	while (column < 3)
	{
		if (isIdentity(curr))
		{
			cout << "answer implement later";
			return;
		}

		if (curr.checkAllZeroes(column))
		{
			pivot--;
			cout << "column has all zeroes" << endl;
		}

		if (curr.containsOne(column, pivot) && !curr.otherRowsZero(column, pivot))
		{
			if (curr.selectRow(pivot)[column] != 1)
			{
				cout << "im here " << endl;
				int lead = curr.checkForOne(column, pivot);
				curr.switchRow(lead, row);
			}
			curr.MakeZeroes(column, pivot);
			pivnum++;
		}
		else if (curr.otherRowsZero(column, pivot)) // check if already ready to divide
		{
			if(curr.selectRow(pivot)[column] != 0)
				curr.rowDivide(pivot, curr.selectRow(pivot)[column]);
			cout << "other rows equal zero" << endl;
			pivnum++;
		}

		else if (curr.selectRow(pivot)[column] != 0) // 
		{
			int value = curr.selectRow(pivot)[column];
			if(value != 0)
				curr.rowDivide(pivot, value);
			curr.MakeZeroes(column, curr.checkForOne(column, pivot));
			pivnum++;

			cout << "pivot position not equal to zero, divide" << endl;
		}
		else if (curr.checkForOne(column, pivot) != -1 && !curr.otherRowsZero(column, pivot))
		{
			if (!(curr.selectRow(pivot)[column] == 1))
			{
				int lead = curr.checkForOne(column, pivot);
				curr.switchRow(row, lead);
			}
			curr.MakeZeroes(column, pivot);
			pivnum++;
		}
		else if (!curr.containsOne(column, pivot) && curr.selectRow(pivot)[column] == 0)
		{

			//while (column != 2 && curr.selectRow(pivot)[column] == 0) // if last row pivot = 0 then the row should already be zero.
			//{
			//	bool checked = false;
			//	if (row = 1 && !checked)
			//	{
			//		curr.switchRow(row, row + 2);
			//	}
			//	else
			int lead = curr.firstLead(pivot, column);
			curr.switchRow(row, lead);
			

			if(curr.selectRow(pivot)[column] != 0)
			curr.rowDivide(pivot, curr.selectRow(pivot)[column]);
			curr.MakeZeroes(column, pivot);
			pivnum++;

			cout << "column doesnt have lead 1 and pivot position equal 0" << endl;
		}
		row++;
		column++;
		pivot++;
		cout << curr << endl;
		M = curr;
		displaySolution(curr, pivnum);
	}
}

int main()
{
	Matrix m;
	int track = 11;
	int row = 1;

  cout<<"You will be asked to enter a 3x4 augmented matrix one cell at a time. You will enter the right hand side of the matrix after the other values. The calculator will solve for the RREF of the entered matrix."<<endl<<endl;

	for (int a = 1; a < 4; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			cout << "Enter a" << track << ": ";
			int temp;
			cin >> temp;
			m.inputCoefficient(a, b, temp);
			track++;
		}
		track += 7;


	}

	for (int a = 1; a <= 3; a++)
	{
		cout << "\nenter rhs";
		int temp;
		cin >> temp;
		m.alterRHS(a, temp);
	}
	cout << endl << m << endl;

	cout << "Testing RREF of Matrix";
	solveMatrix(m);
	//m.MakeZeroes(0, 1);
	//cout << endl << m;

	/*
  
  ***Testing Individual functions in matrix.h***

  cout << "Testing basic add of r1 and r2";
	m.basicAdd(1, 2);
	cout << endl << m; \

	cout << "Testing complex add of (-1)r1 and (3)r3";
	m.complexAdd(-1, 1, 3, 3);
	cout << endl << m;

	cout << "Testing switch of r1 and r2";
	m.switchRow(1, 2);
	cout << endl << m;

	cout << "Testing switch of r1 and r3";
	m.switchRow(1, 3);
	cout << endl << m;

	cout << "Testing switch of r2 and r3";
	m.switchRow(2, 3);
	cout << endl << m;*/


	//cout << "Testing multiplication of -1 * r2";
	//m.rowMultiply(2, -1);
	
	system("pause");

	return 0;
}
