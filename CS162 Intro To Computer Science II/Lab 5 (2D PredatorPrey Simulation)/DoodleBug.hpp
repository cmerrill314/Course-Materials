/* DoodleBug.hpp is the DoodleBug class specification file.*/

#include "Critter.hpp"

//include guard
#ifndef DOODLEBUG_HPP 
#define DOODLEBUG_HPP

class DoodleBug : public Critter
{
public:
	DoodleBug(char sprt) : Critter(sprt) {}; //constructor

	int move(int, int, Critter*, Critter*, Critter*, Critter*);  //determines if/where a doodlebug will move
	int breed(int, int, Critter*, Critter*, Critter*, Critter*); //determines if/where a doodlebug will breed
};

#endif