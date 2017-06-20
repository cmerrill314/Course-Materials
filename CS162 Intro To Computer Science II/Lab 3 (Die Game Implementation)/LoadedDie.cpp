#include "LoadedDie.hpp"

#include <cstdlib> //required for rand() 

/*********************************************************************
**                            LoadedDie::loadedRoll
** Returns a loaded roll value. Since the die is loaded, it has a 50%
** chance of rolling the highest possible value. 
*********************************************************************/
int LoadedDie::loadedRoll()
{
	int rollValue; //stores the value of the roll
	int chance;    //determines whether or not the roll results in the max value for the die

	chance = rand() % 2 + 1;  //creates a random value of 1 or 2 (50% chance)

	//the following if/else statement decides if the die will roll a maximum value based on the value of chance.
	if (chance == 2)
		rollValue = sideCount; //the die will roll a maximum value
	else
		rollValue = rand() % sideCount + 1; //generates a random value between 1 and sideCount

	return rollValue;
}