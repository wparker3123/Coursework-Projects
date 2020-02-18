#pragma once
#include <cstring>
#include <iostream>
using namespace std;



class Matrix
{
public:
	Matrix()
	{
		/*for (double a = 0; a < 3; a++)
		{
			double*& temp = selectRow(a);
			for (double b = 0; b < 4; b++)
				temp[b] = 0;
			r1[a] = num * r1[a];
		}*/
	}

	Matrix(double* row1, double* row2, double* row3)
	{
		r1 = row1;
		r2 = row2;
		r3 = row3;
	}
	//Create default matrix of size 3x3 with values set to 3 dynamic arrays

	void inputCoefficient(double row, int pos, double value) {
		if (row == 1)
			r1[pos] = value;
		else if (row == 2)
			r2[pos] = value;
		else if (row == 3)
			r3[pos] = value;
	}

	void alterRHS(int row, double value)
	{
		switch (row)
		{
		case 1:
			r1[3] = value;
		case 2:
			r2[3] = value;
		case 3:
			r3[3] = value;
		}
	}

	void basicAdd(double row, double r)
	{
		double*& save = selectRow(row);
		double*& use = selectRow(r);
		save[0] += use[0];
		save[1] += use[1];
		save[2] += use[2];
		save[3] += use[3];
	}
	double*& selectRow(int row)
	{
		switch (row)
		{
		case 1:
			return r1;
		case 2:
			return r2;
		default:
			return r3;
		}
	}
	void complexAdd(double snum, int s, double unum, int u)
	{
		double*& save = selectRow(s);
		double*& use = selectRow(u);

		for (int a = 0; a <= 3; a++) {
			save[a] = (save[a] * snum) + (unum * use[a]);
		}
		/*
		save[0] = (save[0] * snum) + (unum * use[0]);
		save[1] = (save[1] * snum) + (unum * use[1]);
		save[2] = (save[2] * snum) + (unum * use[2]);
		save[3] = (save[3] * snum) + (unum * use[3]);
		*/
	}

	void switchRow(double rowNum, double otherRowNum)
	{
		cout << "swapping R" << rowNum << " and R" << otherRowNum;
		double*& r1 = selectRow(rowNum);
		double*& r2 = selectRow(otherRowNum);
		double* temp = r1;

		r1 = r2;
		r2 = temp;
	}
	/*void cancelOut(int col, int pivot) 
	{
		switch (pivot)
		{
		case 1:
		{
			if(selectRow(2))
		}
		}
	}*/
	void MakeZeroes(int column, int leadPos)
	{
		//if(selectRow(leadPos)[column] == 0 && leadPos > )
			
		switch (leadPos)
		{
			case 1:
			{
				if (r2[column] != 0)
				{
					cout << "R2 = R2 + -" << r2[column] << "R1" << endl;
					complexAdd(1, 2, -1 * r2[column], 1);
				}
					
				if (r3[column] != 0)
				{
					cout << "R3 = R3 + -" << r3[column] << "R1" << endl;
					complexAdd(1, 3, -1 * r3[column], 1);
				}
				break;
			}

			case 2:
			{
				if (r1[column] != 0)
				{
					cout << "R1 = R1 + -" << r1[column] << "R2" << endl;
					complexAdd(1, 1, -1 * r1[column], 2);
				}

				if (r3[column] != 0)
				{
					cout << "R3 = R3 + -" << r3[column] << "R3" << endl;
					complexAdd(1, 3, -1 * r3[column], 2);
				}
				break;
			}
			case 3:
			{
				if (r1[column] != 0)
				{
					cout << "R1 = R1 + -" << r1[column] << "R3" << endl;
					complexAdd(1, 1, -1 * r1[column], 3);
					
				}

				if (r2[column] != 0)
				{
					cout << "R2 = R2 + " << -r2[column] << "R3" << endl;
					complexAdd(1, 2, -1 * r2[column], 3);
				}
				break;
			}

		}

	}
	void rowDivide(int row, double num)
	{
		double*& r1 = selectRow(row);
		for (int a = 0; a <= 3; a++)
		{
			r1[a] = (1/num) * r1[a];
		}
		cout << "Dividing R" << row << " by " << num << endl;
	}
	bool checkAllZeroes(int column)
	{
		column -= 1;
		return r1[column] == 0 && r2[column] == 0 && r3[column] == 0;
	
	}
	void makeIdentityMatrix()
	{
		inputCoefficient(1, 0, 1);
		inputCoefficient(2, 1, 1);
		inputCoefficient(3, 2, 1);
	}
	bool containsOne(int col, int pivot)
	{
		for (int a = pivot; a <= 3; a++)
		{
			if (selectRow(a)[col] == 1)
				return true;
		}
		return false;
	}
	int checkForOne(int col, int currentPivot)
	{
		for (int a = currentPivot; a <= 3; a++)
		{
			if (selectRow(a)[col] == 1)
				return a;
		}
		return -1;
	}
	int firstLead(int pivot, int col)
	{
		if (!checkAllZeroes(col))
		{
			for (int a = pivot; a <= 3; a++)
			{
				if (selectRow(a)[col] != 0)
					return a;
			}
		}
    return -1;
	}
	bool hasPivot(int column)
	{
		return containsOne(column, 1) && otherRowsZero(column, checkForOne(column, 1));
	}
	bool otherRowsZero(int column, int pivot)
	{
		switch (pivot)
		{
			case 1:
			{
				if (selectRow(1)[column] != 0 && selectRow(2)[column] == 0 && selectRow(3)[column] == 0)
					return true;
			}
			case 2:
			{
				if (selectRow(2)[column] != 0 && selectRow(1)[column] == 0 && selectRow(3)[column] == 0)
					return true;
			}

			case 3:
			{
				if (selectRow(3)[column] != 0 && selectRow(1)[column] == 0 && selectRow(2)[column] == 0)
					return true;
			}
		}
		return false;
	}
	bool identityRow(int column)
	{
		int pos = checkForOne(column, column);
		if (pos == -1)
			return false;

		selectRow(column)[pos] -= 1;

		if (!checkAllZeroes(column))
			return false; 

		selectRow(column)[pos] += 1;

		return true;
	}
	double* operator [](int row)
	{
		switch (row)
		{
			case 1:
				return r1;
			case 2:
				return r2;
			default:
				return r3;
		}
	}

	friend bool operator != (const Matrix &c1, const Matrix &c2);
	friend bool operator == (const Matrix &c1, const Matrix &c2);
	friend ostream & operator<<(std::ostream & Str, const Matrix& m);
	//Add solution set in an array.


private:
	double* r1 = new double[4];
	double* r2 = new double[4];
	double* r3 = new double[4];
};

ostream & operator<<(std::ostream & Str, const Matrix& m) {
	// prdouble something from v to str, e.g: Str << v.getX();
	//t select = 1;


	Str << m.r1[0] << " " << m.r1[1] << " " << m.r1[2] << "|" << m.r1[3] << endl;
	Str << m.r2[0] << " " << m.r2[1] << " " << m.r2[2] << "|" << m.r2[3] << endl;
	Str << m.r3[0] << " " << m.r3[1] << " " << m.r3[2] << "|" << m.r3[3] << endl;
	return Str;
}
bool operator == (const Matrix &c1, const Matrix &c2)
{
	Matrix m = c1;
	Matrix m2 = c2;
	for (int a = 0; a < 3; a++)
	{
		double*& r1 = m.selectRow(a);
		double*& r2 = m2.selectRow(a);
		for (int c = 0; c < 3; c++)
		{
			if (r1[c] != r2[c])
				return false;
		}
	}
	return true;
}

bool operator != (const Matrix &c1, const Matrix &c2)
{
	if (!(c1 == c2))
		return true;
	return false;
}
