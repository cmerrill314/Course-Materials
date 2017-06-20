#include "determinant.hpp"

/*********************************************************************
**                        determinant
** The determinant function returns the determinant for the matrix that 
** the user enters. It takes a pointer to a matrix and the size of
** the matrix as a parameter. Depending on the size, the corresponding
** determinant equation is used. 
*********************************************************************/

int determinant(int** mtrx, int size)
{
	int determinant; //holds the value of the determinant of the user's matrix

	//if it is a 2x2 matrix, use the formula for the determinant of a 2x2 matrix
	if (size == 2)
	{
		determinant = (mtrx[0][0] * mtrx[1][1]) - (mtrx[0][1] * mtrx[1][0]);
	}
	//if it is a 3x3 matrix, use the formula for the determinant of a 3x3 matrix
	else if (size == 3)
	{
		determinant = (mtrx[0][0] * ((mtrx[1][1] * mtrx[2][2]) - (mtrx[1][2] * mtrx[2][1]))) - (mtrx[0][1] * ((mtrx[1][0] * mtrx[2][2]) - (mtrx[1][2] * mtrx[2][0]))) + (mtrx[0][2] * ((mtrx[1][0] * mtrx[2][1]) - (mtrx[1][1] * mtrx[2][0])));
	}

	return determinant;
}