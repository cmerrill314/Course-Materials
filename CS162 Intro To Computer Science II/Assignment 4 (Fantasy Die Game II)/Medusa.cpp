#include "Medusa.hpp"
#include <cstdlib> //required for rand() 

/*********************************************************************
** Function: Medusa::attack
**
** Description: Controls the attack function for the medusa type.
** rand() is used to generate a random roll of two 6-sided die.
** If the resulting roll equals 12, medusa's glare power is enacted.
**
** Return: Returns the result of the attack die roll.
*********************************************************************/
int Medusa::attack()
{
	//roll the attack die
	int dieOne = rand() % atkDieSides + 1;
	int dieTwo = rand() % atkDieSides + 1;
	int rollValue = dieOne + dieTwo;

	//if the roll is 12, activate glare
	if (rollValue == 12)
	{
		this->powerEnacted = true;
		return rollValue;
	}
	else
		return rollValue;
}

/*********************************************************************
** Function: Medusa::defend
**
** Description: Controls the defend function for the Medusa type.
** rand() is used to generate a random roll of one 6-sided die. 
**
** Parameters: The int value of the opponents attack is taken as a 
** parameter.
**
** Return: Returns the damage done.
*********************************************************************/
int Medusa::defend(int attack)
{
	//roll the defense die
	int rollValue = rand() % defDieSides + 1;

	//calculate the damage done
	int damage = attack - rollValue - this->armor;

	//if damage done is greater than zero, make the damage equal to zero
	if (damage < 0)
		damage = 0;

	//update strength
	this->strength -= damage;

	return damage;
}