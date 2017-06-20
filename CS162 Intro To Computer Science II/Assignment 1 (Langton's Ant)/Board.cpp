#include "Board.hpp"

#include <iostream>
#include <string>
using std::cout;
using std::endl;

//default constructor definition
Board::Board()
{
	sizeRow = 1;
	sizeCol = 1;
}

/*********************************************************************
**                        Board::makeBoard
** Creates the game board, which is a dynamically allocated 2D array,
** using the row and column size entered by the user. It then initializes
** all tile values to be "white".
*********************************************************************/
void Board::makeBoard()
{
	//dynamically allocate a 2D array according to the user's size input
	board = new std::string*[sizeRow];
	for (int i = 0; i < sizeRow; ++i)
		board[i] = new std::string[sizeCol];
	//initialize all board values to be white
	for (int i = 0; i < sizeRow; i++)
		for (int j = 0; j < sizeCol; j++)
			board[i][j] = "-";
}

/*********************************************************************
**                        Board::print
** Prints out each value of the game board array, and separates the 
** lines accordingly.
*********************************************************************/
void Board::print()
{
	//print out each value of the board array
	for (int i = 0; i < sizeRow; i++)
		for (int j = 0; j < sizeCol; j++)
		{
			cout << board[i][j];
			//if you reach the end of a line, start a new line
			if (j == (sizeCol - 1))
				cout << endl;
		}
}

/*********************************************************************
**                        Board::getTileValue
** Retrieves the current value of a particular tile of the game board
** (white or black).
*********************************************************************/
std::string Board::getTileValue(int row, int col)
{
	return board[row][col];
}

/*********************************************************************
**                        Board::getSizeRow
** Retrieve the row size of the game board, as specified by the user.
*********************************************************************/
int Board::getSizeRow()
{
	return sizeRow;
}

/*********************************************************************
**                        Board::getSizeCol
** Retrieve the column size of the game board, as specified by the user.
*********************************************************************/
int Board::getSizeCol()
{
	return sizeCol;
}

/*********************************************************************
**                        Board::setTileValue
** Changes a particular tile of the game row to be white or black.
*********************************************************************/
void Board::setTileValue(int row, int col, std::string value)
{
	board[row][col] = value;
}

/*********************************************************************
**                        Board::setSizeRow
** Sets the row size of the game board.
*********************************************************************/
void Board::setSizeRow(int row)
{
	sizeRow = row;
}

/*********************************************************************
**                        Board::setSizeCol
** Sets the column size of the game board. 
*********************************************************************/
void Board::setSizeCol(int col)
{
	sizeCol = col;
}