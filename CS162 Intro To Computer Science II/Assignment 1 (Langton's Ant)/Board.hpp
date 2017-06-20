/* Board.hpp is the Board class specification file.*/

#include <string>

//include guard
#ifndef BOARD_HPP 
#define BOARD_HPP

class Board
{
private:
	std::string** board; //the game board
	int sizeRow;         //the number of rows in the game board
	int sizeCol;         //the number of columns in the game board
public:
	Board();                                //default constructor
	void print();                           //prints the game board
	void makeBoard();                       //creates the game board
	std::string getTileValue(int,int);      //retrieves the value of a particular tile
	int getSizeRow();                       //retrieves the number of rows in the game board
	int getSizeCol();                       //retrieves the number of columns in the game board
	void setTileValue(int,int,std::string); //sets a tile value to white or black
	void setSizeRow(int);                   //sets the number of rows in the game board
	void setSizeCol(int);                   //sets the number of columns in the game board
};

#endif