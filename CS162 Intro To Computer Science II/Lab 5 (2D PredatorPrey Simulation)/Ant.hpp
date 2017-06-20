/* Ant.hpp is the Ant class specification file.*/

#include "Critter.hpp"

//include guard
#ifndef ANT_HPP 
#define ANT_HPP

class Ant : public Critter
{
public:
	Ant(char sprt): Critter(sprt) {}; //constructor

	int move(int, int, Critter*,Critter*,Critter*,Critter*);     //determines if/where an ant will move
	int breed(int, int, Critter*, Critter*, Critter*, Critter*); //determines if/where an ant will breed
};

#endif