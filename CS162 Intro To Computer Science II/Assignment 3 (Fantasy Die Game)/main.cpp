/*********************************************************************
** Program Filename: battle
** Author: Christopher Merrill
** Date: 10/30/2016
**
** Description: Fantasy die rolling game. Two players choose their 
** hero type and then a series of random die rolls results in a winner.
** There are five hero types: Vampire, Barbarian, Blue Men, Medusa and
** Harry Potter. Each hero type is a sub-class of the hero base class, 
** each with their own unique attack and defend functions. The battles
** take place within the combat class, which handles the game logic. 
**
** Input: The user will input which type of hero each player will use.
**
** Output: The results of each round will be displayed to the console
** until a winner is determined, at which point the user will have the
** option to play again or exit the program.
*********************************************************************/

#include "Combat.hpp"
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
		cout << endl;
		cout << "*****************************************************************************" << endl;
		cout << "*                          STACK/QUEUE LIST CREATOR                         *" << endl;
		cout << "*****************************************************************************" << endl;
		cout << "*   Which type of list would you like to make?                              *" << endl;
		cout << "*                                                                           *" << endl;
		cout << "*   1. Stack                                                                *" << endl;
		cout << "*   2. Queue                                                                *" << endl;
		cout << "*   3. Exit                                                                 *" << endl;
		cout << "*                                                                           *" << endl;
		cout << "*****************************************************************************" << endl << endl;

		//ask for the users selection 
		choice = getInteger("Enter your choice: ");

		//if the user enters 1, prompt for the character decisions and play the game
		if (choice == 1)
		{
			cout << endl;
			cout << "*****************************************************************************" << endl;
			cout << "*                                STACK LIST                                 *" << endl;
			cout << "*****************************************************************************" << endl;
			cout << "*   What would you like to do?                                              *" << endl;
			cout << "*                                                                           *" << endl;
			cout << "*   1. Push                                                                 *" << endl;
			cout << "*   2. Pop                                                                  *" << endl;
			cout << "*   3. Return to Main Menu                                                  *" << endl;
			cout << "*                                                                           *" << endl;
			cout << "*****************************************************************************" << endl << endl;
			
			int choiceTwo = getInteger("Enter your choice: ");
			
			//create a new stack object
			Stack list;
		}
		else if (choice == 2)
		{

		}

	} while (choice != 3);

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
	while (num <= 0 || num > 3)
	{
		cout << "Invalid choice. Please enter one of the menu options instead." << endl;
		cin.clear();
		cin.ignore();
		cin >> num;
	}

	return num;
}