#include "BlueMen.hpp"
#include <cstdlib> //required for rand() 

/*********************************************************************
** Function: BlueMen::attack
**
** Description: Controls the attack function for the blue men type.
** rand() is used to generate a random roll of two 10-sided die.
**
** Return: Returns the result of the attack die roll.
*********************************************************************/
int BlueMen::attack()
{
	//roll the attack die
	int dieOne = rand() % atkDieSides + 1;
	int dieTwo = rand() % atkDieSides + 1;
	int rollValue = dieOne + dieTwo;
	return rollValue;
}

/*********************************************************************
** Function: BlueMen::defend
**
** Description: Controls the defend function for the BlueMen type.
** rand() is used to generate a random roll of three 6-sided die. Mob 
** effect: for every four damage the blue men takes, they lose one 
** defense die.
**
** Parameters: The int value of the opponents attack is taken as a 
** parameter.
**
** Return: Returns the damage done.
*********************************************************************/
int BlueMen::defend(int attack)
{
	int rollValue;
	int initialStrength = this->strength;
	
	//roll the defense die
	int dieOne = rand() % defDieSides + 1;
	int dieTwo = rand() % defDieSides + 1;
	int dieThree = rand() % defDieSides + 1;

	//determine how many die are used based on the mob effect
	if (this->strength > 8)
		rollValue = dieOne + dieTwo + dieThree;
	else if (this->strength > 4)
		rollValue = dieOne + dieTwo;
	else
		rollValue = dieOne;

	//calculate damage done
	int damage = attack - rollValue - this->armor;

	//if damage done is greater than zero, make the damage equal to zero
	if (damage < 0)
		damage = 0;

	//update strength
	this->strength -= damage;

	//activate mob if necessary
	if ((initialStrength > 8 && strength <= 8)|| (initialStrength > 4 && strength <= 4))
		this->powerEnacted = true;

	return damage;
}