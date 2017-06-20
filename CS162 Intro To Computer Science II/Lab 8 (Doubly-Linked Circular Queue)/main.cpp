/*********************************************************************
** Program Filename:
** Author: Christopher Merrill
** Date: 11/20/2016
**
** Description: Lab 8. Implementation of an doubly-linked circular 
** structure. Utilizes a Queue class to manage QueueNode structures. The
** user has the ability to add values to the queue, display the first
** node in the queue, remove the first node in the queue, and display
** the queue. 
*********************************************************************/

#include "Queue.hpp"

#include <string>
#include <iostream>
using namespace std;

int getInteger(std::string); //input validation function

int main()
{
	int choice;
	Queue list; //instantiate a Queue object

	do
	{
		cout << endl;
		cout << "**************************************************************" << endl;
		cout << "*                         MAIN MENU                          *" << endl;
		cout << "**************************************************************" << endl;
		cout << "*   What would you like to do?                               *" << endl;
		cout << "*                                                            *" << endl;
		cout << "*   1. Enter a value to be added to the queue                *" << endl;
		cout << "*   2. Display the first node (front) value                  *" << endl;
		cout << "*   3. Remove the first node (front) value                   *" << endl;
		cout << "*   4. Display the queue contents (contents will be deleted) *" << endl;
		cout << "*   5. Exit                                                  *" << endl;
		cout << "*                                                            *" << endl;
		cout << "**************************************************************" << endl << endl;

		//ask for the user's selection 
		choice = getInteger("Enter your choice:");
		cout << endl;

		//ADD BACK OPTION:
		if (choice == 1)
		{
			//ask the user to input a value to add to the back of the queue
			int value = getInteger("Enter an integer value to add to the queue:");

			//input validation
			while (value <= 0)
			{
				cout << "ERROR: Invalid entry. ";
				value = getInteger("Enter an integer value greater than 0:");
			}

			//run the addback function
			list.addBack(value);
		}
		//GET FRONT OPTION:
		else if (choice == 2)
		{
			//if the list is empty, provide an error message
			if (list.getFront() == -1)
			{
				cout << "ERROR: The Queue is empty. ";
			}
			
			//display the first node
			cout << "The first node value is: " << list.getFront() << endl;
		}
		//REMOVE FRONT OPTION:
		else if (choice == 3)
		{
			//if the list is empty, provide an error message
			if (list.getFront() == -1)
			{
				cout << "ERROR: The list is empty. " << endl;
			}

			//display the list contents
			cout << "You have removed the value: " << list.removeFront() << endl;
		}
		//DISPLAY QUEUE OPTION:
		else if (choice == 4)
		{
			int temp = list.getFront();

			//if the list is empty, provide an error message
			if (temp == -1)
			{
				cout << "ERROR: The list is empty, nothing to display. " << endl;
			}
			//otherwise display the list contents
			else
			{
				cout << "The contents of your list are:" << endl;

				//continue to remove list items until the front node is empty
				while (temp != -1)
				{
					cout << list.removeFront() << " ";
					temp = list.getFront();
				}
				cout << endl << endl;
			}
		}
		//input validation
		else if (choice != 5)
			cout << "ERROR: Invalid choice, please choose one of the menu options below:";
	} while (choice != 5);

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