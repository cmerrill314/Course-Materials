/*********************************************************************
** Program Filename: buffer
** Author: Christopher Merrill
** Date: 11/22/2016
**
** Description: Lab 9. Utilized STL stack/queue containers to create
** a buffer simulation and a palindrom creator. The user can decide 
** which function to run by choosing a menu option. 
**
** Input: For the buffer simulation, the user inputs the number of
** turns, the probability of adding a value and the probability of
** removing a value. For the palindrome creator, the user enters a 
** string. 
**
** Output: For the buffer simulation, the average length of the buffer
** (after all the rounds are completed) is displayed. For the palindrome 
** creator, the palindrom is displayed. 
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
		cout << "************************************" << endl;
		cout << "*            MAIN MENU             *" << endl;
		cout << "************************************" << endl;
		cout << "*   What would you like to do?     *" << endl;
		cout << "*                                  *" << endl;
		cout << "*   1. Run the buffer simulator    *" << endl;
		cout << "*   2. Run the palindrome creator  *" << endl;
		cout << "*   3. Exit                        *" << endl;
		cout << "*                                  *" << endl;
		cout << "************************************" << endl << endl;

		//ask for the user's selection 
		choice = getInteger("Enter your choice: ");

		//BUFFER SIMULATION OPTION
		if (choice == 1)
		{
			cout << endl;
			//ask the user to input the number of terms, and the various probabilities
			int turns = getInteger("How many turns should the simulate run?:");
			int valueOne = getInteger("What is the probablitity an item will be added? (Enter an integer from 0-100):");
			int valueTwo = getInteger("What is the probablitity an item will be removed? (Enter an integer from 0-100):");

			//instantiate a buffer object, run the simulation and display the average
			Queue buffer(turns, valueOne, valueTwo);
			cout << endl;
			cout << "AVERAGE BUFFER LENGTH: " << buffer.runSimulation() << endl;
		}
		//PALINDROME OPTION
		else if (choice == 2)
		{
			std::string word;
			cout << endl;

			//ask the user to input a string
			cout << "Enter a string to turn into a palindrome: " << endl;
			cin.clear();
			cin.ignore();
			getline(cin, word);

			//instantiate a Stack object and display the palindrome
			Stack pal(word);
			cout << endl;
			cout << "PALINDROME: " << pal.createPal() << endl << endl;
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