#include "Barbarian.hpp"
#include <cstdlib> //required for rand() 

/*********************************************************************
** Function: Barbarian::attack
**
** Description: Controls the attack function for the barbarian type.
** rand() is used to generate a random roll of two 6-sided die.
**
** Return: Returns the result of the attack die roll.
*********************************************************************/
int Barbarian::attack()
{
	//roll the attack die
	int dieOne = rand() % atkDieSides + 1;
	int dieTwo = rand() % atkDieSides + 1;
	int rollValue = dieOne + dieTwo;
	return rollValue;
}

/*********************************************************************
** Function: Barbarian::defend
**
** Description: Controls the defend function for the barbarian type.
** rand() is used to generate a random roll of two 6-sided die. 
**
** Parameters: The int value of the opponents attack is taken as a 
** parameter.
**
** Return: Returns the damage done.
*********************************************************************/
int Barbarian::defend(int attack)
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

	return damage;
}