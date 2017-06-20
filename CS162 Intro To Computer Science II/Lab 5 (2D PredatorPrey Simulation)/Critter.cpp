#include "Critter.hpp"

/*********************************************************************
** Function: Critter::Critter
**
** Description: Default constructor for Critter objects. 
*********************************************************************/
Critter::Critter()
{

	sprite = ' ';
	steps = 0;
	hunger = 0;
	hasMoved = false;
}

/*********************************************************************
** Function: Critter::Critter
**
** Description: Constructor for Critter objects.
**
** Parameters: Takes a character as input which determines the sprite 
** of a critter (X for doodlebugs, O for ants).
*********************************************************************/
Critter::Critter(char sprt)
{
	this->sprite = sprt;
	this->steps = 0;
	this->hunger = 0;
	this->hasMoved = false;
}

/*********************************************************************
** Function: Critter::getSprite
**
** Description: Getter function for a critter's sprite value.
**
** Return: Returns a critter's sprite value.
*********************************************************************/
char Critter::getSprite()
{
	return this->sprite;
}

/*********************************************************************
** Function: Critter::getSteps
**
** Description: Getter function for a critter's steps value.
**
** Return: Returns a critter's steps value.
*********************************************************************/
int Critter::getSteps()
{
	return this->steps;
}

/*********************************************************************
** Function: Critter::getHunger
**
** Description: Getter function for a critter's hunger value.
**
** Return: Returns a critter's hunger value.
*********************************************************************/
int Critter::getHunger()
{
	return this->hunger;
}

/*********************************************************************
** Function: Critter::getHasMoved
**
** Description: Getter function for a critter's hasMoved value.
**
** Return: Returns a critter's hasMoved value (true means a critter
** has moved during this time step, false means a critter has yet to 
** move during this time step).
*********************************************************************/
bool Critter::getHasMoved() 
{
	return this->hasMoved;
}

/*********************************************************************
** Function: Critter::setHasMoved
**
** Description: Setter function for a critter's hasMoved value.
**
** Parameters: Takes a bool as input. (true means a critter
** has moved during this time step, false means a critter has yet to 
** move during this time step).
*********************************************************************/
void Critter::setHasMoved(bool value)
{
	this->hasMoved = value;
}