#include "Board.hpp"
#include "Ant.hpp"
#include "DoodleBug.hpp"

#include <iostream>
#include <string>
#include <cstdlib> //required for rand() and srand()
#include <ctime>   //required to seed rand()
#include <unistd.h> //needed to pause the game between printing
using std::rand;
using std::srand;
using std::cout;
using std::endl;

/*********************************************************************
** Function: Board::Board
**
** Description: Default constructor for board objects. Initializes all
** game board values to be empty, then randomly places 100 ants and 5
** doodlebugs onto the gameboard.
*********************************************************************/
Board::Board()
{
	srand(time(0));
	pauseTime = 25000;

	int randomRow = rand() % 20;
	int randomCol = rand() % 20;

	
	//initialize all board values to empty
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			board[i][j] = NULL;

	//place 100 ants on the board
	for (int i = 0; i < 100; i++)
	{
		//if the random location is empty, place an ant there
		if (board[randomRow][randomCol] == NULL)
		{
			board[randomRow][randomCol] = new Ant('O');
		}
		//otherwise continue searching for a random empty location
		else
		{
			while (board[randomRow][randomCol] != NULL)
			{
				randomRow = rand() % 20;
				randomCol = rand() % 20;
			}
			board[randomRow][randomCol] = new Ant('O');
		}
	}

	//place 5 doodlebugs on the board
	for (int i = 0; i < 5; i++)
	{
		//if the random location is empty, place a doodlebug there
		if (board[randomRow][randomCol] == NULL)
		{
			board[randomRow][randomCol] = new DoodleBug('X');
		}
		//otherwise continue searching for a random empty location
		else
		{
			while (board[randomRow][randomCol] != NULL)
			{
				randomRow = rand() % 20;
				randomCol = rand() % 20;
			}
			board[randomRow][randomCol] = new DoodleBug('X');
		}
	}
}

/*********************************************************************
** Function: Board::print
**
** Description: Scans each element of the game board array to search 
** for ants and doodlebugs. Depending on which critter is found (or if
** no critter is found) the display board is updated with the 
** corresponding character: X for doodlebugs, O for ants, and blank for
** empty. The display board is then printed to the screen using cout. 
** 
** Return: Displays the game board to the console.
*********************************************************************/
void Board::print()
{
	//scan each element in the board. If the value is null, set the equivalent tile in the display board to 'E'
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			if (board[i][j] == NULL)
				display[i][j] = ' ';
			else if (board[i][j]->getSprite() == 'O')
				display[i][j] = 'O';
			else if (board[i][j]->getSprite() == 'X')
				display[i][j] = 'X';
		}

	//print out each value of the display board array
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			cout << display[i][j] << " ";
			//if you reach the end of a line, start a new line
			if (j == 19)
				cout << endl;
		}
}

/*********************************************************************
** Function: Board::play
**
** Description: Runs the main game loop for the program. First the 
** board is printed to the console. Then the game loop is executed for
** the specified number of time steps. The game loop consists of the 
** following: First move the doodlebugs, then carry out any doodlebug
** breeding, then move the ants, then carry out any ant breeding, then
** carry out any doodlebug starving. Finally, print the updated board
** to the console using the print function. 
**
** Parameters: An integer value which represents the user specified
** number of time steps to carry out. 
**
** Return: Displays the updated game board to the console after each
** time step is carried out
*********************************************************************/
void Board::play(int timeSteps)
{
	int count = 0; // the current turn number
	
	//print the initial game board
	print();

	//execute main game loop
	do
	{
		//doodlebugs move first, so loop through the board to find and move doodlebugs
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 20; j++)
			{
				//check to see if the given tile contains a critter
				if (board[i][j] != NULL)
				{
					//check to see if the given tile contains a doodlebug
					if (board[i][j]->getSprite() == 'X')
					{
						//run the move function
						int direction = board[i][j]->move(i, j, board[i - 1][j], board[i + 1][j], board[i][j - 1], board[i][j + 1]);

						//update the board with the move
						if (direction == 1)
						{
							board[i - 1][j] = board[i][j];
							board[i][j] = NULL;
						}
						else if (direction == 2)
						{
							board[i + 1][j] = board[i][j];
							board[i][j] = NULL;
						}
						else if (direction == 3)
						{
							board[i][j - 1] = board[i][j];
							board[i][j] = NULL;
						}
						else if (direction == 4)
						{
							board[i][j + 1] = board[i][j];
							board[i][j] = NULL;
						}
					}
				}
			}

		//check the board for doodlebugs that are ready to breed
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 20; j++)
			{
				if (board[i][j] != NULL)
				{
					if (board[i][j]->getSprite() == 'X' && board[i][j]->getSteps() == 8)
					{
						//run the breed function
						int direction = board[i][j]->breed(i, j, board[i - 1][j], board[i + 1][j], board[i][j - 1], board[i][j + 1]);

						//update the board with the newly born ant
						if (direction == 1)
						{
							board[i - 1][j] = new DoodleBug('X');
						}
						else if (direction == 2)
						{
							board[i + 1][j] = new DoodleBug('X');
						}
						else if (direction == 3)
						{
							board[i][j - 1] = new DoodleBug('X');
						}
						else if (direction == 4)
						{
							board[i][j + 1] = new DoodleBug('X');
						}
					}
				}
			}

		//now move the ants
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 20; j++)
			{
				//check to see if the given tile contains a critter
				if (board[i][j] != NULL)
				{
					//check to see if the given tile contains aan ant
					if (board[i][j]->getSprite() == 'O')
					{
						//run the move function
						int direction = board[i][j]->move(i, j, board[i - 1][j], board[i + 1][j], board[i][j - 1], board[i][j + 1]);

						//update the board with the move
						if (direction == 1)
						{
							board[i - 1][j] = board[i][j];
							board[i][j] = NULL;
						}
						else if (direction == 2)
						{
							board[i + 1][j] = board[i][j];
							board[i][j] = NULL;
						}
						else if (direction == 3)
						{
							board[i][j - 1] = board[i][j];
							board[i][j] = NULL;
						}
						else if (direction == 4)
						{
							board[i][j + 1] = board[i][j];
							board[i][j] = NULL;
						}
					}
				}
			}

		//settle ant breeding and doodlebug starving
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 20; j++)
			{
				if (board[i][j] != NULL)
				{
					//return all critters has-moved value to false
					board[i][j]->setHasMoved(false);

					//check the board for ants that are ready to breed
					if (board[i][j]->getSprite() == 'O' && board[i][j]->getSteps() == 3)
					{
						//run the breed function
						int direction = board[i][j]->breed(i, j, board[i - 1][j], board[i + 1][j], board[i][j - 1], board[i][j + 1]);

						//update the board with the newly born ant
						if (direction == 1)
						{
							board[i - 1][j] = new Ant('O');
						}
						else if (direction == 2)
						{
							board[i + 1][j] = new Ant('O');
						}
						else if (direction == 3)
						{
							board[i][j - 1] = new Ant('O');
						}
						else if (direction == 4)
						{
							board[i][j + 1] = new Ant('O');
						}
					}

					//check for starving doodlebugs
					if (board[i][j]->getHunger() == 3)
						board[i][j] = NULL;
				}
			}	

		//clear the board, print the next frame and update the turn number
		usleep(pauseTime);                   
		cout << "\033[2J\033[1;1H" << endl;   
		print();    
		count++;

	} while (count < timeSteps);
}

/*********************************************************************
** Function: Board::cleanUp
**
** Description: Cleans up the memory allocated in Board using delete.
*********************************************************************/
void Board::cleanUp()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			if (board[i][j] != NULL)
				delete board[i][j];
}