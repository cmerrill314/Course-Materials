/* Board.hpp is the Board class specification file.*/

#include "Critter.hpp"
#include <string>

//include guard
#ifndef BOARD_HPP 
#define BOARD_HPP

class Board
{
private:
	Critter* board[20][20]; //the game board
	char display[20][20];   //converts the object values in the game board to chars (O, X or E)
	int pauseTime;          //the amount of time between frames

public:
	Board();         //default constructor
	void print();    //prints the game board
	void play(int);  //the main play loop for the simulation
	void cleanUp();  //frees the memory allocated in board
};

#endif