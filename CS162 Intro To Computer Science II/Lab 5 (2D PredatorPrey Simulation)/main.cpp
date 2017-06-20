/*********************************************************************
** Program Filename: prey
** Author: Christopher Merrill
** Date: 10/30/2016
**
** Description: 2D predator/prey simulation. Consists of ants (O) and
** doodlebugs (X). Doodlebugs eat ants, if they dont eat an ant within
** three steps then they will die of starvation. If an ant survives 
** three steps without being eaten, it will breed. If a doodlebug 
** survives eight steps without being eaten, it will breed. 
**
** The simulation will run for the specified number of steps. Once 
** finished, the user will be able to specify if they want to continue
** the simulation or if they want to exit the program.
**
** Input: The user will input the number of time steps to execute 
**
** Output: A 20x20 grid will be displayed, updating after each time
** step, to show the movement patterns of the ants and doodlebugs. 
*********************************************************************/

#include "Board.hpp"

#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;

//input validation function
int getInteger(std::string);

int main()
{
	Board brd;
	int choice;

	cout << endl;
	cout << "*********************************************" << endl;
	cout << "*        2D PREDATOR/PREY SIMULATION        *" << endl;
	cout << "*********************************************" << endl;
	cout << "* What would you like to do?                *" << endl;
	cout << "*                                           *" << endl;
	cout << "* 1. Run Simulation                         *" << endl;
	cout << "* 2. Exit                                   *" << endl;
	cout << "*                                           *" << endl;
	cout << "*********************************************" << endl << endl;

	//ask for the users selection 
	choice = getInteger("Enter your choice: ");

	do
	{
		//if the user enters 1, ask for the number of time steps and then run the simulation
		if (choice == 1)
		{
			int steps = getInteger("For how many time steps would you like the simulation to run?: ");
			brd.play(steps);
		}
		//if the user enters an invalid number, notify them and allow for another choice
		else if (choice != 2)
			cout << "Invalid choice. Please choose one of the menu options instead:" << endl << endl;

		cout << endl;
		cout << "*********************************************" << endl;
		cout << "*        2D PREDATOR/PREY SIMULATION        *" << endl;
		cout << "*********************************************" << endl;
		cout << "* What would you like to do?                *" << endl;
		cout << "*                                           *" << endl;
		cout << "* 1. Continue Simulation                    *" << endl;
		cout << "* 2. Exit                                   *" << endl;
		cout << "*                                           *" << endl;
		cout << "*********************************************" << endl << endl;

		//ask for the users selection 
		choice = getInteger("Enter your choice: ");

	} while (choice != 2);

	//run cleanup
	brd.cleanUp();

	return 0;
}

/*********************************************************************
** Function: getInteger
**
** Description: Input validation function for integers.
**
** Parameters: A single string, which is the prompt that asks the user
** for a specific input.
**
** Return: Returns an integer which has been verified to be a 
** non-negative and non-zero integer.
*********************************************************************/
int getInteger(std::string prompt)
{
	int num;

	//run the desired prompt
	cout << prompt << endl;
	cin >> num;

	//if the number entered was not an integer, prompt the user to try again
	while (!cin)
	{
		cout << "Invalid choice. Please enter an integer value instead." << endl;
		cin.clear();  //clear the error flag on cin
		cin.ignore(); //skip to the next new line
		cin >> num;
	}

	//if the integer entered was not greater than zero, prompt the user to try again
	while (num <= 0)
	{
		cout << "Invalid choice. Please enter an integer that is greater than zero." << endl;
		cin.clear();
		cin.ignore();
		cin >> num;
	}

	return num;
}