/* Critter.hpp is the Critter class specification file.*/

#include <string>

//include guard
#ifndef CRITTER_HPP 
#define CRITTER_HPP

class Critter
{
protected:
	char sprite;   //the character value of the critter (O, X, or blank)
	int steps;     //the number of steps since breeding
	bool hasMoved; //determines whether or not a critter has already moved in a given time step
	int hunger;    //the number of steps since a critters' last meal (applicable only to doodlebugs)

public:
	Critter();     //default constructor
	Critter(char); //constructor

	//virtual move and breed functions. used by both ants and doodlebugs
	virtual int breed(int, int, Critter*, Critter*, Critter*, Critter*) { return 0; };
	virtual int move(int, int, Critter*, Critter*, Critter*, Critter*) { return 0; };

	char getSprite();       //returns a critters sprite value
	int getSteps();         //returns the number of steps a critter has moved since breeding
	int getHunger();        //retunrs the number of steps a doodlebug has moved since eating
	bool getHasMoved();     //returns whether or not a critter has moved during a given time step
	void setHasMoved(bool); //sets whether or not a critter has moved during a given time step
};

#endif