/* Die.hpp is the Die class specification file.*/

//include guards
#ifndef DIE_HPP 
#define DIE_HPP

class Die
{
public:
	int sideCount;   //the number of sides on the die

	Die(int);        //constructor
	int roll();      //determines the value of a dice roll
};

#endif