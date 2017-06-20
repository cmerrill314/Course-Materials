/*********************************************************************
** Program Filename: battle
** Author: Christopher Merrill
** Date: 10/30/2016
**
** Description: This program runs a tournament of head to head battles
** between the creatures we created for Assignment 3. The tournament 
** consists of two teams, Team A and Team B. The user specifies the 
** number of creatures each Team will have in their lineup. The lineups
** are held within queue-like structures (created in lab 6). The loser
** of each round is removed from the lineup and placed in a stack-like
** structure (created in lab 6) called the "loser pile". The winner of
** each round is moved to the end of its team's lineup. 
**
** Once a team is out of players the tournament is over, at which point
** the winner and each team finals score is displayed. The user will then
** have the option to view the contents of the loser pile.
**
** The battles that take place in each round of tournament are conducted 
** using the Combat class's "play" method, which was created in Assignment
** 3. 
**
** Input: The user inputs the number of creatures on each team's lineup,
** as well as which creatures will populate each team's lineup.
**
** Output: The starting lineup, the results of each round, and the winner 
** of the tournament are all displayed. There is also the optional output
** of the loser pile. 
*********************************************************************/

#include "Tournament.hpp"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

//input validation function
int getInteger(std::string);

int main()
{
	int choice;

	do
	{
		//display the main meny
		cout << endl;
		cout << "**********************************" << endl;
		cout << "*            MAIN MENU           *" << endl;
		cout << "**********************************" << endl;
		cout << "* What would you like to do?     *" << endl;
		cout << "*                                *" << endl;
		cout << "* 1. Run a tournament            *" << endl;
		cout << "* 2. Exit                        *" << endl;
		cout << "**********************************" << endl << endl;

		choice = getInteger("Enter your choice:");

		//if the user chooses to run a tournamnet
		if (choice == 1)
		{
			int numHeros;

			//ask the user how many heros should be in each teams lineup
			cout << endl;
			numHeros = getInteger("How many heros would you like on each team?");

			//create a tournament object using the specified number of heros
			Tournament battle(numHeros);

			//populate each team's lineup and run the play loop
			battle.populate();
			battle.play();
		}

	} while (choice != 2);
	
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
		cout << "Invalid choice. Please enter an integer greater than zero." << endl;
		cin.clear();
		cin.ignore();
		cin >> num;
	}

	return num;
}