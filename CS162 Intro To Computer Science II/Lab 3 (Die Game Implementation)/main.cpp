/*********************************************************************
** Name: Christopher Merrill
** Course: CS162
** Date: 10/11/2016
**
** Description: 
**
** Two players roll their respective die and the highest
** value wins the round. The player with the highest score after the
** specified number of rounds wins the game. The user decides how many
** sides are on each player's die, and whether or not a player's die
** is loaded or not. The program consists of a Game class (which contains
** the main game loop and keeps track of each player's score and stats), 
** a Die class (which contains all the information for a standard die as
** well as a standard roll function), and a LoadedDie class (which is 
** inherited from Die, but contains a loaded roll function that favors
** the highest value on the die). 
*********************************************************************/

#include "Die.hpp"
#include "LoadedDie.hpp"
#include "Game.hpp"

#include <string>
#include <iostream>
using namespace std;

int getInteger(std::string); //input validation function

int main()
{
	std::string one;
	std::string two;

	//introduction
	cout << endl;
	cout << "*********************************************************************" << endl;
	cout << "**                 WELCOME TO THE UNFAIR DICE GAME                 **" << endl;
	cout << "*********************************************************************" << endl << endl;

	//ask the user how many sides should be on each player's die
	int dieOneSides = getInteger("How many sides should Player One's die have?");
	int dieTwoSides = getInteger("How many sides should Player Two's die have?");
	cout << endl;

	//ask the user if Player One's die should be loaded on unloaded
	cout << "Is Player One's die Loaded or Unloaded?" << endl;
	int choiceOne = getInteger("Enter 1 for Loaded or 2 for Unloaded:");

	//validate input 
	while (choiceOne != 1 && choiceOne != 2)
	{
		choiceOne = getInteger("Invalid choice. Please enter 1 or 2:");
	}

	//set the unloaded/loaded value for player one
	if (choiceOne == 1)
		one = "Loaded";
	else
		one = "Unloaded";

	//ask the user if Player Two's die should be loaded on unloaded
	cout << "Is Player Two's die Loaded or Unloaded?" << endl;
	int choiceTwo = getInteger("Enter 1 for Loaded or 2 for Unloaded:");

	//validate input 
	while (choiceTwo != 1 && choiceTwo != 2)
	{
		choiceTwo = getInteger("Invalid choice. Please enter 1 or 2:");
	}

	//set the unloaded/loaded value for player two
	if (choiceTwo == 1)
		two = "Loaded";
	else
		two = "Unloaded";

	//ask the user how many rounds they would like to play
	cout << endl;
	int rounds = getInteger("How many rounds would you like to play?");

	//instantiate the game class using the loaded/unloaded choices for player one and player two
	Game game(one, two, rounds);

	//run the game loop using the number of sides on player one and player two's die. 
	game.play(dieOneSides, dieTwoSides);

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