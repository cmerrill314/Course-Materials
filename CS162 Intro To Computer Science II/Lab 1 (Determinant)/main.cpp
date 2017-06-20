/*********************************************************************
** Author: Christopher Merrill
** Course: CS162
** Assignment: Lab 1
** Date: 9/27/2016
** Description: This program calculates the determinant of a 2x2 or 3x3
** matrix, the values of which are entered by the user. 
*********************************************************************/

#include "determinant.hpp"
#include "readMatrix.hpp"

#include <iostream>
using namespace std;

int main()
{
	int matrixSize; //holds the size of the matrix

	//ask the user which size matrix they would like
	cout << "What size matrix would you like, 2x2 or 3x3? (Enter 2 or 3)" << endl;
	cin >> matrixSize;
	cout << endl;

	//initialize a blank 2x2 ir 3x3 matrix, depending on the user's size selection
	int** matrix = new int*[matrixSize];
	for (int i = 0; i < matrixSize; ++i)
		matrix[i] = new int[matrixSize];

	//read in the values of the matrix using the readMatrix function
	readMatrix(matrix, matrixSize);

	//display the matrix
	cout << "For the following matrix: " << endl << endl;
	if (matrixSize == 2)
	{
		cout << matrix[0][0] << " " << matrix[0][1] << endl;
		cout << matrix[1][0] << " " << matrix[1][1] << endl << endl;
	}
	else if (matrixSize == 3)
	{
		cout << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << endl;
		cout << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << endl;
		cout << matrix[2][0] << " " << matrix[2][1] << " " << matrix[2][2] << endl << endl;
	}

	//calculate the determinant using the determinant function and display the result
	cout << "The determinant equals " << determinant(matrix, matrixSize) << "." << endl;

	return 0;
}