#include "Combat.hpp"

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
** Parameters: 
*********************************************************************/
Combat::Combat(Hero* one, Hero* two)
{
	playerOne = one;
	playerTwo = two;

	playerOneText = "Team A";
	playerTwoText = "Team B";
	winner = "";
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
	bool winnerDeclared = false;

	Hero* firstPlayer;
	Hero* secondPlayer;

	//the following strings are used to display "Team A" and "Team B" in the correct locations
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

		//if first player is medusa and medusa uses glare, note the winner and end the loop
		if (firstPlayer->getPowerEnacted() && firstPlayer->getName() == "Medusa")
		{
			winner = firstText;
			winnerDeclared = true;
		}
		else
		{
			//if first player won the game, note the winner and end the loop
			if (secondPlayer->getStrength() <= 0)
			{
				winner = firstText;
				winnerDeclared = true;
			}
			else
			{
				//reset power enacted to false for both players
				firstPlayer->setPowerEnacted(false);
				secondPlayer->setPowerEnacted(false);

				//make the second attack/defense rolls
				int atkTwoValue = secondPlayer->attack();
				int defTwoValue = firstPlayer->defend(atkTwoValue);

				//if second player is medusa and medusa uses glare, note the winner and end the loop
				if (secondPlayer->getPowerEnacted() && secondPlayer->getName() == "Medusa")
				{
					winner = secondText;
					winnerDeclared = true;
				}
				//if second player won the game, note the winner and end the loop
				else if (firstPlayer->getStrength() <= 0)
				{
					winner = secondText;
					winnerDeclared = true;
				}	
			}
		}

		//reset power enacted to false for both players 
		firstPlayer->setPowerEnacted(false);
		playerTwo->setPowerEnacted(false);

	} while (!winnerDeclared);

	//reset power enacted to false for both players 
	firstPlayer->setPowerEnacted(false);
	playerTwo->setPowerEnacted(false);

	//reset hogwarts used to false for both players
	firstPlayer->setHogwartsUsed(false);
	secondPlayer->setHogwartsUsed(false);

	//heal the winner
	int healValue = heal();

	//display the round results
	cout << "Team A's " << playerOne->getName() << " vs. Team B's " << playerTwo->getName() << ", ";
	cout << winner << " wins!" << endl;

	if (winner == "Team A")
	{
		cout << "Team B's " << playerTwo->getName() << " was sent to the loser pile..." << endl;
		cout << "Team A's " << playerOne->getName() << " was healed " << healValue << " strength point(s)." << endl << endl;
	}
	else
	{
		cout << "Team A's " << playerOne->getName() << " was sent to the loser pile..." << endl;
		cout << "Team B's " << playerTwo->getName() << " was healed " << healValue << " strength point(s)." << endl << endl;
	}
}

/*********************************************************************
** Function: Combat::heal
**
** Description: Heals the winner of a particular round. A random number
** between 1 and 5 is generated, which represents the number of strength
** points the winner will be healed. There is also a check at the end
** that assures that a particular hero isn't left with more strength 
** then they origianally start with after the heal. 
*********************************************************************/
int Combat::heal()
{
	int roll = rand() % 5 + 1;
	int healValue;
	
	//if team A wins, heal that team's hero
	if (winner == "Team A")
	{
		int currentStrength = playerOne->getStrength();

		if (roll == 1)
		{
			healValue = 1; 
			playerOne->setStrength(currentStrength + healValue);
		}
		else if (roll == 2)
		{
			healValue = 2; 
			playerOne->setStrength(currentStrength + healValue);
		}
		else if (roll == 3)
		{
			healValue = 3; 
			playerOne->setStrength(currentStrength + healValue);
		}
		else if (roll == 4)
		{
			healValue = 4; 
			playerOne->setStrength(currentStrength + healValue);
		}
		else 
		{
			healValue = 5; 
			playerOne->setStrength(currentStrength + healValue);
		}
			
		//don't allow a hero to have more strength then they originally start with
		if (playerOne->getName() == "Vampire")
		{
			if (playerOne->getStrength() > 18)
				playerOne->setStrength(18);
		}
		else if (playerOne->getName() == "Barbarian" || playerOne->getName() == "Blue Men")
		{
			if (playerOne->getStrength() > 12)
				playerOne->setStrength(12);
		}
		else if (playerOne->getName() == "Medusa")
		{
			if (playerOne->getStrength() > 8)
				playerOne->setStrength(8);
		}
		else
		{
			if (playerOne->getStrength() > 10)
				playerOne->setStrength(10);
		}
	}
	//if team B wins, heal that team's hero
	else
	{
		int currentStrength = playerTwo->getStrength();

		if (roll == 1)
		{
			healValue = 1;
			playerTwo->setStrength(currentStrength + healValue);
		}
		else if (roll == 2)
		{
			healValue = 2;
			playerTwo->setStrength(currentStrength + healValue);
		}
		else if (roll == 3)
		{
			healValue = 3;
			playerTwo->setStrength(currentStrength + healValue);
		}
		else if (roll == 4)
		{
			healValue = 4;
			playerTwo->setStrength(currentStrength + healValue);
		}
		else
		{
			healValue = 5;
			playerTwo->setStrength(currentStrength + healValue);
		}

		//don't allow a hero to have more strength then they originally start with
		if (playerTwo->getName() == "Vampire")
		{
			if (playerTwo->getStrength() > 18)
				playerTwo->setStrength(18);
		}
		else if (playerTwo->getName() == "Barbarian" || playerTwo->getName() == "Blue Men")
		{
			if (playerTwo->getStrength() > 12)
				playerTwo->setStrength(12);
		}
		else if (playerTwo->getName() == "Medusa")
		{
			if (playerTwo->getStrength() > 8)
				playerTwo->setStrength(8);
		}
		else
		{
			if (playerTwo->getStrength() > 10)
				playerTwo->setStrength(10);
		}
	}

	return roll;
}