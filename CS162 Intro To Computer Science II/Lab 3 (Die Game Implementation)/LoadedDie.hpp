/* LoadedDie.hpp is the LoadedDie class specification file.*/

#include "Die.hpp"

#include <cstdlib> //required for rand() and srand()
#include <ctime>   //required to seed rand()

//include guards
#ifndef LOADEDDIE_HPP 
#define LOADEDDIE_HPP

class LoadedDie: public Die
{
public:
	LoadedDie(int sides) :Die(sides) {srand(time(0));}; //constructor
	int loadedRoll();                    //performs a loaded die roll
};

#endif