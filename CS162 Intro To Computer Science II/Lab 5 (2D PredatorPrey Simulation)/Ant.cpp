#include "Ant.hpp"
#include <cstdlib> //required for rand() and srand()
#include <ctime>   //required to seed rand()

/*********************************************************************
** Function: Ant::move
**
** Description: Decides if the ant is able to move. If it is able 
** to move, then an int value is returned representing the direction the
** ant will move.
**
** Parameters: Takes the row and column information for the ant, to 
** determine if the ant is positioned on a boundary. Takes four pointers
** to critters, which are the values of the grid tiles above, below, to
** the left, and to the right of the ant to determine if there is 
** available space for movement
**
** Return: Returns an integer value which represents the direction the
** ant will move: 
** 
** 0: No movement
** 1: Move up
** 2: Move down
** 3: Move left
** 4: Move right
*********************************************************************/
int Ant::move(int row, int col, Critter* up, Critter* down, Critter* left, Critter* right)
{
	//the following variables represent the availability of each possible direction
	bool upAvailable = true;
	bool downAvailable = true;
	bool leftAvailable = true;
	bool rightAvailable = true;

	//if the critter has already moved, return 0
	if (this->hasMoved == true)
		return 0;

	//if the critter is on a boundary or a given direction is already taken, update availability
	if (row == 0 || up != NULL)
		upAvailable = false;
	if (row == 19 || down != NULL)
		downAvailable = false;
	if (col == 0 || left != NULL)
		leftAvailable = false;
	if (col == 19 || right != NULL)
		rightAvailable = false;

	//if all neighboring tiles are unavailable, return 0
	if (!upAvailable && !downAvailable && !leftAvailable && !rightAvailable)
		return 0;

	//otherwise choose a random available direction to move
	int luck = rand() % 4 + 1; //generates a random number between 1 and 4

	//if luck is 1, favor up
	if (luck == 1)
	{
		if (upAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 1;
		}	
		else if (downAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 2;
		}
		else if (leftAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 3;
		}
		else if (rightAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 4;
		}
	}
	//if luck is 2, favor down
	else if (luck == 2)
	{
		if (downAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 2;
		}
		else if (leftAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 3;
		}
		else if (rightAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 4;
		}
		else if (upAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 1;
		}
	}
	//if luck is 3, favor left
	else if (luck == 3)
	{
		if (leftAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 3;
		}
		else if (rightAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 4;
		}
		else if (upAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 1;
		}
		else if (downAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 2;
		}
	}
	//if luck is 4, favor right
	else if (luck == 4)
	{
		if (rightAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 4;
		}
		else if (upAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 1;
		}
		else if (downAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 2;
		}
		else if (leftAvailable)
		{
			this->steps += 1;
			this->hasMoved = true;
			return 3;
		}
	}
}

/*********************************************************************
** Function: Ant::breed
**
** Description: Decides if the ant is able to breed. If it is able
** to breed, then an int value is returned representing the direction the
** ant will breed in.
**
** Parameters: Takes the row and column information for the ant, to
** determine if the ant is positioned on a boundary. Takes four pointers
** to critters, which are the values of the grid tiles above, below, to
** the left, and to the right of the ant to determine if there is
** available space for breeding.
**
** Return: Returns an integer value which represents the direction the
** ant will breed:
**
** 0: No room for breeding
** 1: Breed up
** 2: Breed down
** 3: Breed left
** 4: Breed right
*********************************************************************/
int Ant::breed(int row, int col, Critter* up, Critter* down, Critter* left, Critter* right)
{
	//the following variables represent the availability to breed in each possible direction
	bool upAvailable = true;
	bool downAvailable = true;
	bool leftAvailable = true;
	bool rightAvailable = true;

	//if the critter is on a boundary or a given direction is already taken, update availability
	if (row == 0 || up != NULL)
		upAvailable = false;
	if (row == 19 || down != NULL)
		downAvailable = false;
	if (col == 0 || left != NULL)
		leftAvailable = false;
	if (col == 19 || right != NULL)
		rightAvailable = false;

	//if all neighboring tiles are unavailable, return 0 and the ant will have to wait 3 more turns to breed
	if (!upAvailable && !downAvailable && !leftAvailable && !rightAvailable)
	{
		this->steps = 0;
		return 0;
	}

	//otherwise choose a random available direction to breed 
	int luck = rand() % 4 + 1; //generates a random number between 1 and 4

	//if luck is 1, favor up
	if (luck == 1)
	{
		if (upAvailable)
		{
			this->steps = 0;
			return 1;
		}
		else if (downAvailable)
		{
			this->steps = 0;
			return 2;
		}
		else if (leftAvailable)
		{
			this->steps = 0;
			return 3;
		}
		else if (rightAvailable)
		{
			this->steps = 0;
			return 4;
		}
	}
	//if luck is 2, favor down
	else if (luck == 2)
	{
		if (downAvailable)
		{
			this->steps = 0;
			return 2;
		}
		else if (leftAvailable)
		{
			this->steps = 0;
			return 3;
		}
		else if (rightAvailable)
		{
			this->steps = 0;
			return 4;
		}
		else if (upAvailable)
		{
			this->steps = 0;
			return 1;
		}
	}
	//if luck is 3, favor left
	else if (luck == 3)
	{
		if (leftAvailable)
		{
			this->steps = 0;
			return 3;
		}
		else if (rightAvailable)
		{
			this->steps = 0;
			return 4;
		}
		else if (upAvailable)
		{
			this->steps = 0;
			return 1;
		}
		else if (downAvailable)
		{
			this->steps = 0;
			return 2;
		}
	}
	//if luck is 4, favor right
	else if (luck == 4)
	{
		if (rightAvailable)
		{
			this->steps = 0;
			return 4;
		}
		else if (upAvailable)
		{
			this->steps = 0;
			return 1;
		}
		else if (downAvailable)
		{
			this->steps = 0;
			return 2;
		}
		else if (leftAvailable)
		{
			this->steps = 0;
			return 3;
		}
	}
}