#include "Die.hpp"
#include <cstdlib> //required for rand() and srand()
#include <ctime>   //required to seed rand()
using std::rand;
using std::srand;

//constructor definition
Die::Die(int sides)
{
	sideCount = sides;
	srand(time(0));  //seeds the random number generator
}

/*********************************************************************
**                            Die::roll
** Returns a random integer between 1 and the number of sides on the 
** die. Simulates a "roll" of the die. 
*********************************************************************/
int Die::roll()
{
	int rollValue = rand() % sideCount + 1; //generates a random value between 1 and sideCount
	return rollValue;
}