#include "Hero.hpp"
#include <string>
#include <cstdlib> //required for rand() and srand()
#include <ctime>   //required to seed rand()

//hero class default constructor
Hero::Hero()
{
	name = " ";
	armor = 0;
	strength = 0;
	atkDieSides = 0;
	defDieSides = 0;
	powerEnacted = false;
	hogwartsUsed = false;

	srand(time(0));
}

/*********************************************************************
** Function: Hero::Hero
**
** Description: Constructor for the hero class. Initializes all 
** necessary values for a given class. Also seeds the random number
** generator used throughout the program.
**
** Parameters: Takes a string value which represents the name of the 
** desired class.
*********************************************************************/
Hero::Hero(std::string value, std::string teamName)
{
	srand(time(0));
	this->powerEnacted = false;
	this->team = teamName;

	if (value == "vampire")
	{
		this->name = "Vampire";
		this->strength = 18;
		this->armor = 1;
		this->atkDieSides = 12;
		this->defDieSides = 6;
	}
	else if (value == "barbarian")
	{
		this->name = "Barbarian";
		this->strength = 12;
		this->armor = 0;
		this->atkDieSides = 6;
		this->defDieSides = 6;
	}
	else if (value == "bluemen")
	{
		this->name = "Blue Men";
		this->strength = 12;
		this->armor = 3;
		this->atkDieSides = 10;
		this->defDieSides = 6;
	}
	else if (value == "medusa")
	{
		this->name = "Medusa";
		this->strength = 8;
		this->armor = 3;
		this->atkDieSides = 6;
		this->defDieSides = 6;
	}
	else if (value == "harrypotter")
	{
		this->name = "Harry Potter";
		this->strength = 10;
		this->armor = 0;
		this->atkDieSides = 6;
		this->defDieSides = 6;
		this->hogwartsUsed = false;
	}
}