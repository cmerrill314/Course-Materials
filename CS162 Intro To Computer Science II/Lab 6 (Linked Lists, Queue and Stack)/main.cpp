/*********************************************************************
** Program Filename: structures
** Author: Christopher Merrill
** Date: 11/6/2016
**
** Description: This program lets a user create either a stack-like
** structure or a queue-like structure. With either option, they can
** either push (add items) or pop (remove items).
**
** Input: The user decides if they want to create a stack-like structure
** or a queue-like structure. They then input if they want to push or pop.
**
** Output: The updated list of integers is displayed after each action 
** the user completes.
*********************************************************************/

#include "Queue.hpp"
#include "Stack.hpp"

#include <string>
#include <iostream>
using namespace std;

int getInteger(std::string); //input validation function

int main()
{
	int choice;

	do
	{
		cout << endl;
		cout << "*****************************************************************************" << endl;
		cout << "*                       STACK/QUEUE STRUCTURE CREATOR                       *" << endl;
		cout << "*****************************************************************************" << endl;
		cout << "*   Which type of structure would you like to make?                         *" << endl;
		cout << "*                                                                           *" << endl;
		cout << "*   1. Stack-Like                                                           *" << endl;
		cout << "*   2. Queue-Like                                                           *" << endl;
		cout << "*   3. Exit                                                                 *" << endl;
		cout << "*                                                                           *" << endl;
		cout << "*****************************************************************************" << endl << endl;

		//ask for the user's selection 
		choice = getInteger("Enter your choice: ");

		//if the user enters 1, create a stack-like structure
		if (choice == 1)
		{
			//create a new stack object
			Stack list;
			int choiceTwo;

			do
			{
				cout << endl;
				cout << "*****************************************************************************" << endl;
				cout << "*                              STACK STRUCTURE                              *" << endl;
				cout << "*****************************************************************************" << endl;
				cout << "*   What would you like to do?                                              *" << endl;
				cout << "*                                                                           *" << endl;
				cout << "*   1. Push                                                                 *" << endl;
				cout << "*   2. Pop                                                                  *" << endl;
				cout << "*   3. Return to Main Menu                                                  *" << endl;
				cout << "*                                                                           *" << endl;
				cout << "*****************************************************************************" << endl << endl;

				//ask for the user's selection
				choiceTwo = getInteger("Enter your choice: ");

				//if the user enters 1, run the push method
				if (choiceTwo == 1)
				{
					//ask the user for a value to push, then call the push method
					int pushValue = getInteger("Enter an integer value to add to the list: ");
					list.push(pushValue);

					//display the updated list
					cout << "CURRENT LIST: ";
					list.print();
					cout << endl;
				}
				//if the user enters 2, run the pop method
				else if (choiceTwo == 2)
				{
					list.pop();

					//display the updated list
					cout << "CURRENT LIST: ";
					list.print();
					cout << endl;
				}
			} while (choiceTwo != 3);
		}
		else if (choice == 2)
		{
			//create a new stack object
			Queue list;
			int choiceTwo;

			do
			{
				cout << endl;
				cout << "*****************************************************************************" << endl;
				cout << "*                                QUEUE LIST                                 *" << endl;
				cout << "*****************************************************************************" << endl;
				cout << "*   What would you like to do?                                              *" << endl;
				cout << "*                                                                           *" << endl;
				cout << "*   1. Push                                                                 *" << endl;
				cout << "*   2. Pop                                                                  *" << endl;
				cout << "*   3. Return to Main Menu                                                  *" << endl;
				cout << "*                                                                           *" << endl;
				cout << "*****************************************************************************" << endl << endl;

				//ask for the user's selection
				choiceTwo = getInteger("Enter your choice: ");

				//if the user enters 1, run the push method
				if (choiceTwo == 1)
				{
					//ask the user for a value to push, then call the push method
					int pushValue = getInteger("Enter an integer value to add to the list: ");
					list.push(pushValue);

					//display the updated list
					cout << "CURRENT LIST: ";
					list.print();
					cout << endl;
				}
				//if the user enters 2, run the pop method
				else if (choiceTwo == 2)
				{
					list.pop();

					//display the updated list
					cout << "CURRENT LIST: ";
					list.print();
					cout << endl;
				}
				else if (choiceTwo != 3)
					cout << "Invalid choice, please choose one of the menu options instead:";
			} while (choiceTwo != 3);
		}
		else if (choice != 3)
			cout << "Invalid choice, please choose one of the menu options instead:";
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

	return num;
}