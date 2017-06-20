/*********************************************************************
** Name: Christopher Merrill
** Course: CS162
** Date: 10/23/2016
** Description: Creates a grocery list with user entered items. 
** allows the user to add and remove items, and keeps track of the grand 
** of all items added. 
*********************************************************************/

#include "List.hpp"
#include <iostream>
using namespace std;

//input validation functions
int getInteger(std::string); 
double getDouble(std::string prompt);

int main()
{
	List groceries; //grocery list
	int choice;

	do
	{
		//allocate new memory if necessary
		groceries.allocate();

		cout << "*********************************************" << endl;
		cout << "*                    MENU                   *" << endl;
		cout << "*********************************************" << endl;
		cout << "* What would you like to do?                *" << endl;
		cout << "*                                           *" << endl;
		cout << "* 1. Add Item                               *" << endl;
		cout << "* 2. Remove Item                            *" << endl;
		cout << "* 3. Exit                                   *" << endl;
		cout << "*                                           *" << endl;
		cout << "*********************************************" << endl << endl;

		//ask for the users selection 
		choice = getInteger("Enter your choice: ");

		//if the user enters 1, add an item to the list
		if (choice == 1)
		{
			std::string name;
			std::string units;

			//ask for the item details: name, quantity, units, unit cost
			cout << "Enter the item's name: " << endl;
			cin.clear();
			cin.ignore();
			getline(cin, name);
			int quantity = getInteger("Enter the desired quantity: ");
			cout << "Enter the units of the item (box, gallon, etc.): " << endl;
			cin.clear();
			cin.ignore();
			getline(cin, units);
			double unitCost = getDouble("Enter the cost per unit: ");

			//clear the console
			cout << "\033[2J\033[1;1H" << endl;

			//add item to the list 
			groceries.addItem(name, units, quantity, unitCost);

			//display the updated list
			cout << "*********************************************" << endl;
			cout << "GROCERY LIST" << endl;
			cout << "*********************************************" << endl;
			groceries.printList();
			cout << endl;
			cout << "GRAND TOTAL: $" << groceries.getGrandTotal() << endl;
			cout << "*********************************************" << endl;
		}
		//if the user enters 2, remove an item from the list
		else if (choice == 2)
		{
			std::string item;

			//ask which item to remove
			cout << "Enter the name of the item you want to remove: " << endl;
			cin.clear();
			cin.ignore();
			getline(cin, item);

			//clear the console
			cout << "\033[2J\033[1;1H" << endl;

			//remove the specified item
			groceries.removeItem(item);

			//display the updated list
			cout << "*********************************************" << endl;
			cout << "GROCERY LIST" << endl;
			cout << "*********************************************" << endl;
			groceries.printList();
			cout << endl;
			cout << "GRAND TOTAL: $" << groceries.getGrandTotal() << endl;
			cout << "*********************************************" << endl;
		}
		//if the user enters an invalid number, notify them and allow for another choice
		else if (choice != 3)
			cout << "Invalid choice. Please choose one of the menu options instead:" << endl << endl;

	} while (choice != 3);

	return 0;
}

/*********************************************************************
**                        getInteger
** Input validation function for integers. Takes a prompt as input, and
** continues asking the user to input values until a valid integer is
** entered.
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

/*********************************************************************
**                        getDouble
** Input validation function for doubles. Takes a prompt as input, and
** continues asking the user to input values until a valid double is
** entered.
*********************************************************************/
double getDouble(std::string prompt)
{
	int dub;

	//run the desired prompt
	cout << prompt << endl;
	cin >> dub;

	//if the number entered was not a double, prompt the user to try again
	while (!cin)
	{
		cout << "Invalid choice. Please enter a double value instead." << endl;
		cin.clear();  //clear the error flag on cin
		cin.ignore(); //skip to the next new line
		cin >> dub;
	}

	//if the double entered was not greater than zero, prompt the user to try again
	while (dub <= 0)
	{
		cout << "Invalid choice. Please enter a double that is greater than zero." << endl;
		cin.clear();
		cin.ignore();
		cin >> dub;
	}

	return dub;
}