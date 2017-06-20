#include "Combat.hpp"
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "Medusa.hpp"
#include "HarryPotter.hpp"

#include <cstdlib> //required for rand() 
#include <string>
#include <iostream>
using std::cout;
using std::endl;

/*********************************************************************
** Function: Combat::Combat
**
** Description: Constructor for the combat class. 
**
** Parameters: Takes two ints, each of which represents a different 
** hero class. Depending on which ints are entered, the corresponding
** hero class will be created for that player:
**
** 1. Vampire
** 2. Barbarian
** 3. BlueMen
** 4. Medusa
** 5. Harry Potter
*********************************************************************/
Combat::Combat(int one, int two)
{
	playerOneText = "Player One";
	playerTwoText = "Player Two";

	if (one == 1)
		playerOne = new Vampire("vampire");
	else if (one == 2)
		playerOne = new Barbarian("barbarian");
	else if (one == 3)
		playerOne = new BlueMen("bluemen");
	else if (one == 4)
		playerOne = new Medusa("medusa");
	else if (one == 5)
		playerOne = new HarryPotter("harrypotter");

	if (two == 1)
		playerTwo = new Vampire("vampire");
	else if (two == 2)
		playerTwo = new Barbarian("barbarian");
	else if (two == 3)
		playerTwo = new BlueMen("bluemen");
	else if (two == 4)
		playerTwo = new Medusa("medusa");
	else if (two == 5)
		playerTwo = new HarryPotter("harrypotter");
}


/*********************************************************************
** Function: Combat::play
**
** Description: Runs the game logic for the battles. The game loop 
** consists of the following: Player one attacks, if a winner is 
** declared the loop ends, if a power is enacted then the user is 
** notified. Then player two attacks, if a winner is declared the loop
** ends, if a power is enacted then the user is notified. The loop runs
** until a winner is declared, at which point the hero the playerOne
** and playerTwo values are deleted.
**
** Return: Displays the results of each round to the screen.
*********************************************************************/
void Combat::play()
{
	int round = 1;
	bool winnerDeclared = false;


	Hero* firstPlayer;
	Hero* secondPlayer;

	//the following strings are used to display "Player One" and "Player Two" in the correct locations
	//regardless of which player goes first. 
	std::string firstText;
	std::string secondText;
	
	//decide which player goes first using rand()
	int roll = rand() % 2 + 1;
	if (roll == 1)
	{
		firstPlayer = playerOne;
		firstText = playerOneText;
		secondPlayer = playerTwo;
		secondText = playerTwoText;
	}
	else
	{
		firstPlayer = playerTwo;
		firstText = playerTwoText;
		secondPlayer = playerOne;
		secondText = playerOneText;
	}

	do 
	{
		//make the first attack/defense rolls
		int atkOneValue = firstPlayer->attack();
		int defOneValue = secondPlayer->defend(atkOneValue);
		cout << "*****************************************************************************" << endl;
		cout << "                               ROUND " << round << " RESULTS: " << endl;
		cout << "*****************************************************************************" << endl << endl;
		cout << firstText << "'s " << firstPlayer->getName() << " rolls an attack of: " << atkOneValue << endl;

		//if medusa uses glare, notify the players and end the game
		if (firstPlayer->getPowerEnacted() && firstPlayer->getName() == "Medusa")
		{
			cout << firstPlayer->getPowerText() << " <" << firstText << " " << firstPlayer->getPowerTextTwo() << endl;
			cout << secondText << "'s " << secondPlayer->getName() << " has been defeated..." << endl;
			cout << "WINNER: " << firstText << "'s " << firstPlayer->getName() << "!!!" << endl << endl;

			winnerDeclared = true;
		}
		else
		{
			//if vampire uses charm, notify the players
			if (secondPlayer->getPowerEnacted() && secondPlayer->getName() == "Vampire")
			{
				cout << secondPlayer->getPowerText() << " <" << secondText << " " << secondPlayer->getPowerTextTwo() << endl;
			}

			//display the first attack results
			cout << secondText << "'s " << secondPlayer->getName() << " was able to defend against: " << (atkOneValue - defOneValue) << endl;
			cout << "Damage to " << secondText << ": " << defOneValue << endl << endl;

			//if harry potter uses hogwarts or blue men use mob, notify the players
			if (secondPlayer->getPowerEnacted() && (secondPlayer->getName() == "Harry Potter" || secondPlayer->getName() == "Blue Men"))
			{
				cout << secondPlayer->getPowerText() << " <" << secondText << " " << secondPlayer->getPowerTextTwo() << endl;
			}

			//if player one won the game, notify the players
			if (secondPlayer->getStrength() <= 0)
			{
				winnerDeclared = true;

				cout << secondText << "'s " << secondPlayer->getName() << " has been defeated..." << endl;
				cout << "WINNER: " << firstText << "'s " << firstPlayer->getName() << "!!!" << endl << endl;
			}
			else
			{
				//reset power enacted to false for both players
				firstPlayer->setPowerEnacted(false);
				secondPlayer->setPowerEnacted(false);

				//make the second attack/defense rolls
				int atkTwoValue = secondPlayer->attack();
				int defTwoValue = firstPlayer->defend(atkTwoValue);

				cout << endl;
				cout << secondText << "'s " << secondPlayer->getName() << " rolls an attack of: " << atkTwoValue << endl;

				//if medusa uses glare, notify the players and end the game
				if (secondPlayer->getPowerEnacted() && secondPlayer->getName() == "Medusa")
				{
					cout << secondPlayer->getPowerText() << " <" << secondText << " " << secondPlayer->getPowerTextTwo() << endl;
					cout << firstText << "'s " << firstPlayer->getName() << " has been defeated..." << endl;
					cout << "WINNER: " << secondText << "'s " << secondPlayer->getName() << "!!!" << endl << endl;

					winnerDeclared = true;
				}
				else
				{
					//if vampire uses charm, notify the players
					if (firstPlayer->getPowerEnacted() && firstPlayer->getName() == "Vampire")
					{
						cout << firstPlayer->getPowerText() << " <" << firstText << " " << firstPlayer->getPowerTextTwo() << endl;
					}

					//display the second attack results
					cout << firstText << "'s " << firstPlayer->getName() << " was able to defend against: " << (atkTwoValue - defTwoValue) << endl;
					cout << "Damage to " << firstText << ": " << defTwoValue << endl << endl;

					//if harry potter uses hogwarts or blue men use mob, notify the players
					if (firstPlayer->getPowerEnacted() && (firstPlayer->getName() == "Harry Potter" || firstPlayer->getName() == "Blue Men"))
					{
						cout << firstPlayer->getPowerText() << " <" << firstText << " " << firstPlayer->getPowerTextTwo() << endl << endl;
					}

					//if player two won the game, notify the players
					if (firstPlayer->getStrength() <= 0)
					{
						winnerDeclared = true;

						cout << firstText << "'s " << firstPlayer->getName() << " has been defeated..." << endl;
						cout << "WINNER: " << secondText << "'s " << secondPlayer->getName() << "!!!" << endl << endl;
					}
					//display the player's remaining strength 
					else
					{
						cout << firstText << "'s Remaining Strength: " << firstPlayer->getStrength() << endl;
						cout << secondText << "'s Remaining Strength: " << secondPlayer->getStrength() << endl << endl;
					}
				}	
			}
		}

		//reset power enacted to false for both players and increment round before starting the loop over
		firstPlayer->setPowerEnacted(false);
		playerTwo->setPowerEnacted(false);
		round++;

	} while (!winnerDeclared);

	//clean up
	delete playerOne;
	delete playerTwo;
}