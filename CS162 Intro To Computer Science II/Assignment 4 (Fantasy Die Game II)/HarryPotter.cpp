#include "HarryPotter.hpp"
#include <cstdlib> //required for rand() 

/*********************************************************************
** Function: HarryPotter::attack
**
** Description: Controls the attack function for the harry potter type.
** rand() is used to generate a random roll of two 6-sided die.
**
** Return: Returns the result of the attack die roll.
*********************************************************************/
int HarryPotter::attack()
{
	//roll the attack die
	int dieOne = rand() % atkDieSides + 1;
	int dieTwo = rand() % atkDieSides + 1;
	int rollValue = dieOne + dieTwo;
	return rollValue;
}

/*********************************************************************
** Function: HarryPotter::defend
**
** Description: Controls the defend function for the Harry Potter type.
** rand() is used to generate a random roll of two 6-sided die. If the 
** damage taken destroys harry potter, then harry potter has one chance 
** to return to life with 20 strength (Hogwarts power). 
**
** Parameters: The int value of the opponents attack is taken as a
** parameter.
**
** Return: Returns the damage done.
*********************************************************************/
int HarryPotter::defend(int attack)
{
	//roll the defense die
	int dieOne = rand() % defDieSides + 1;
	int dieTwo = rand() % defDieSides + 1;
	int rollValue = dieOne + dieTwo;

	//calculate the damage done
	int damage = attack - rollValue - this->armor;

	//if damage done is greater than zero, make the damage equal to zero
	if (damage < 0)
		damage = 0;

	//update strength
	this->strength -= damage;

	//if harry potter dies and hasn't yet used the hogwarts power, use 
	//the hogwarts power
	if (this->strength <= 0 && !this->hogwartsUsed)
	{
		this->hogwartsUsed = true;
		this->powerEnacted = true;
		this->strength = 20;
	}

	return damage;
}