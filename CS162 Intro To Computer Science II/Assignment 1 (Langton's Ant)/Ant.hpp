/* Ant.hpp is the Ant class specification file.*/

#include "Board.hpp"
#include <string>

//include guards
#ifndef ANT_HPP 
#define ANT_HPP

class Ant
{
private:
	Board brd;              //game board, from Board class
	int row;                //the ant's row position
	int column;             //the ant's column position
	int currentStep;        //the ant's current step
	int totalSteps;         //the user specified number of steps to move
	std::string direction;  //the ant's direction
	int totalRows;          //total number of rows in the game board
	int totalColumns;       //total number of columns in the game board
	int pauseTime;          //pause time between frames
public:
	Ant(int, int, int, int, int); //constructor
	void play();                  //main game loop
};

#endif