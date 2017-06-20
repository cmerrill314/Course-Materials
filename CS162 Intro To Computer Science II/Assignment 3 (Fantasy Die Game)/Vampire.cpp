#include "Vampire.hpp"
#include <cstdlib> //required for rand() 

/*********************************************************************
** Function: Vampire::attack
**
** Description: Controls the attack function for the vampire type. 
** rand() is used to generate a random roll of one 12-sided die. 
**
** Return: Returns the result of the attack die roll.
*********************************************************************/
int Vampire::attack()
{
	//roll the attack die
	int rollValue = rand() % atkDieSides + 1;
	return rollValue;
}

/*********************************************************************
** Function: Vampire::defend
**
** Description: Controls the defend function for the vampire type.
** Vampires have a 50% chance to charm their enemy, which is calculated 
** within the charm variable using rand(). If charm is 1, then the default
** defense takes place and rand() is used to generate a random roll of 
** one 6-sided die. If charm is 2, then the opponent is charmed and no
** damage occurs.
**
** Parameters: The int value of the opponents attack is taken as a 
** parameter.
**
** Return: Returns the damage done.
*********************************************************************/
int Vampire::defend(int attack)
{
	//determine if charm will be enacted: 1. No charm, 2. Charm
	int charm = rand() % 2 + 1;

	if (charm == 1)
	{
		//roll the defense die
		int rollValue = rand() % defDieSides + 1;

		//calculate damage done
		int damage = attack - rollValue - this->armor;

		//if damage done is greater than zero, make the damage equal to zero
		if (damage < 0)
			damage = 0;

		//update strength
		this->strength -= damage;

		return damage;
	}
	else
	{
		//enact charm, no damage done
		this->powerEnacted = true;
		return 0;
	}
}