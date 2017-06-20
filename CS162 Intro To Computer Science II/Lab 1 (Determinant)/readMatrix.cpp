#include "readMatrix.hpp"
#include <iostream>
using namespace std;

/*********************************************************************
**                        readMatrix
** The readMatrix function prompts the user to fill in their 2x2 or 3x3
** matrix with values. It takes a pointer to the matrix and the size of 
** the matrix as parameters.
*********************************************************************/

void readMatrix(int** mtrx, int size)
{
	//loop through each row
	for (int i = 0; i < size; i++)
	{
		//loop through each column
		for (int j = 0; j < size; j++)
		{
			//ask the user to enter a value for that particular row/column in their matrix
			cout << "Enter a value for row " << i << " and column " << j << endl;
			cin >> mtrx[i][j];
			cout << endl;
		}
	}
}

