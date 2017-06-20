/*********************************************************************
** Name: Christopher Merrill
** Course: CS162
** Date: 10/4/2016
** Description: The following program runs a simulation of Langton's 
** Ant, a 2D Turing Machine that follows the steps of an ant as it 
** carries out a simple set of instructions. At first the behavior of 
** the ant appears random, but after roughly 10,000 steps a repeating 
** pattern emerges. 
*********************************************************************/

#include "Ant.hpp"
#include "Board.hpp"

#include <iostream>
#include  <cstdlib>
using std::cin;
using std::cout;
using std::endl;
using std::rand;
using std::srand;

//input validation functions (see definitions below)
int getInteger(std::string);
char getChar(std::string);
void makeMenu();


int main()
{
	int rowStart; //holds the ant's starting row position
	int colStart; //holds the ant's starting column position

	//initiate main menu
	makeMenu();

	//ask the user what size array they would like
	int rows = getInteger("How many rows would you like in your array?");
	int columns = getInteger("How many columns would you like in your array?");

	//suggest a number of steps to the user
	cout << "It takes over 10,000 steps to start to see consistent behavior." << endl;
	//ask the user how many steps the ant will take
	int steps = getInteger("How many steps would you like the ant to take?");

	//ask the user if they'd like to specify a starting location
	char choice = getChar("Would you like to choose a starting location? (Y/N)");

	//input validation for yes or no decision
	while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
	{
		cout << "Invalid choice. Please enter Y or N:" << endl;
		cin >> choice;
	}

	//if the user wants to specify a starting location, ask them for coordinates. 
	if (choice == 'Y' || choice == 'y')
	{
		//ask for a starting row value and validate that the inputted value is an integer
		rowStart = getInteger("Please provide a starting row number");
		//validate that the provided row value is within the bounds of the array
		while (rowStart >= rows || rowStart < 0)
		{
			rowStart = getInteger("Please enter a row value that is within the bounds of your array");
		}	
		//ask for a starting column value and validate that the inputted value is an integer
		colStart = getInteger("Please provide a starting column number");
		//validate that the provided row value is within the bounds of the array
		while (colStart >= columns || colStart < 0)
		{
			colStart = getInteger("Please enter a column value that is within the bounds of your array");
		}
		cout << endl;
	}
	//if the user doesn't want to specify a starting location, provide a random location
	else
	{
		srand(time(0));               //seeds the random number generator
		rowStart = rand() % rows;     //selects a random starting row using rand(). 
		colStart = rand() % columns;  //selects a random starting column using rand().
	};

	//instantiate an Ant class and link it to the above board
	Ant ant(rowStart, colStart, rows, columns, steps);

	//start the game
	ant.play();

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
**                        getChar
** Input validation function for characters. Takes a prompt as input, and
** continues asking the user to input values until a valid character is
** entered.
*********************************************************************/
char getChar(std::string prompt)
{
	char character;

	//run the desired prompt
	cout << prompt << endl;
	cin >> character;

	//if the value entered was not a character
	while (!cin)
	{
		cout << "Invalid choice. Please enter a character value instead." << endl;
		cin.clear();  //clear the error flag on cin
		cin.ignore(); //skip to the next new line
		cin >> character;
	}
	return character;
}

/*********************************************************************
**                        makeMenu
** A reusible menu that can be altered for any program. Contains 
** the option to start the game or read the About page.
*********************************************************************/
void makeMenu()
{
	int choice;       //the user's menu selection
	std::string temp; //temporarily holds the value entered to exit choice two (the about section)

	bool state = true;
	//continue the following loop until state is false
	while (state == true)
	{
		//print main menu
		cout << "*************************************************************************" << endl;
		cout << "**                      WELCOME TO LANGTON'S ANT!                      **" << endl;
		cout << "**                                                                     **" << endl;
		cout << "** Please make a selection:                                            **" << endl;
		cout << "**                                                                     **" << endl;
		cout << "** 1. Start Game                                                       **" << endl;
		cout << "** 2. About                                                            **" << endl;
		cout << "**                                                                     **" << endl;
		cout << "*************************************************************************" << endl;

		//take the user's selection
		cin >> choice;

		switch (choice)
		{
		//for choice one, simply exit the loop and start the main function
		case 1:
			state = false;
			break;
		//for choice two, print the about page
		case 2:
			cout << "*************************************************************************" << endl;
			cout << "**                                  ABOUT                              **" << endl;
			cout << "**                                                                     **" << endl;
			cout << "** Langton's Ant is a 2D Turing Machine developed by Chris Langton in  **" << endl;
			cout << "** 1986. It consists of a grid of black and white squares and an ant   **" << endl;
			cout << "** that follows the following simple set of rules:                     **" << endl;
			cout << "**                                                                     **" << endl;
			cout << "**  1.) At a white square, turn 90° right, flip the color of the       **" << endl;
			cout << "**      square, move forward one unit                                  **" << endl;
			cout << "**                                                                     **" << endl;
			cout << "**  2.) At a black square, turn 90° left, flip the color of the        **" << endl;
			cout << "**      square, move forward one unit                                  **" << endl;
			cout << "**                                                                     **" << endl;
			cout << "** At first, the behavior of the ant appears random. However after     **" << endl;
			cout << "** about 10,000 steps, a recurring pattern emerges!                    **" << endl;
			cout << "**                                                                     **" << endl;
			cout << "** This program was created by Christopher Merrill and contains the    **" << endl;
			cout << "** following change to the rules: If the ant moves off the grid, it    **" << endl;
			cout << "** reappears on the other side of the grid (wrap-around behavior).     **" << endl;
			cout << "**                                                                     **" << endl;
			cout << "** ENTER ANY VALUE TO CONTINUE                                         **" << endl;
			cout << "**                                                                     **" << endl;
			cout << "*************************************************************************" << endl;
			cin >> temp;
			break;
		//default to input validation
		default:
			cout << "Invalid choice. Please choose again." << endl;
			cin >> choice;
			break;
		}
	}
}