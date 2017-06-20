#include "Tournament.hpp"
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "Medusa.hpp"
#include "HarryPotter.hpp"

/*********************************************************************
** Function: Tournament::play
**
** Description: Constructor for the tournamnet class. The number of
** heros (and the number of elements in each teams list) are determined
** by a user entered integer that is collected in the main function.
** Each teams score is initialized to 0.
**
** Parameters: Takes a single int which represents the number of heros 
** in each teams starting lineup. 
*********************************************************************/
Tournament::Tournament(int value)
{
	numHeros = value;
	aElements = value;
	bElements = value;

	aPoints = 0;
	bPoints = 0;
}

/*********************************************************************
** Function: Tournament::play
**
** Description: Prompts the user to fill up each team's lineup. As the
** user enters values from the table, a teams queue is populated with
** the corresponding hero using "push".
*********************************************************************/
void Tournament::populate()
{
	cout << endl;
	cout << "**********************************" << endl;
	cout << "*       CHOOSE YOUR LINEUP       *" << endl;
	cout << "**********************************" << endl;
	cout << "* 1. Vampire                     *" << endl;
	cout << "* 2. Barbarian                   *" << endl;
	cout << "* 3. Blue Men                    *" << endl;
	cout << "* 4. Medusa                      *" << endl;
	cout << "* 5. Harry Potter                *" << endl;
	cout << "**********************************" << endl << endl;

	int count = 0;

	//first populate team A's lineup until the count reaches the user-determined number of fighters
	cout << "First determine Team A's lineup" << endl << endl;

	do
	{
		int choice = getInteger("Enter a value from the table above to add it to Team A's lineup:");

		if (choice == 1)
		{
			aLineup.push(new Vampire("vampire", "Team A's"));
			count++;
		}
		else if (choice == 2)
		{
			aLineup.push(new Barbarian("barbarian", "Team A's"));
			count++;
		}
		else if (choice == 3)
		{
			aLineup.push(new BlueMen("bluemen", "Team A's"));
			count++;
		}
		else if (choice == 4)
		{
			aLineup.push(new Medusa("medusa", "Team A's"));
			count++;
		}
		else if (choice == 5)
		{
			aLineup.push(new HarryPotter("harrypotter", "Team A's"));
			count++;
		}
		else
			cout << "Invalid choice...";

	} while (count < numHeros);

	count = 0; // reset count
	cout << endl;

	//then populate team B's lineup until the count reaches the user-determined number of fighters
	cout << "Great, now determine Team B's lineup" << endl << endl;

	do
	{
		int choice = getInteger("Enter a value from the table above to add it to Team B's lineup:");

		if (choice == 1)
		{
			bLineup.push(new Vampire("vampire", "Team B's"));
			count++;
		}
		else if (choice == 2)
		{
			bLineup.push(new Barbarian("barbarian", "Team B's"));
			count++;
		}
		else if (choice == 3)
		{
			bLineup.push(new BlueMen("bluemen", "Team B's"));
			count++;
		}
		else if (choice == 4)
		{
			bLineup.push(new Medusa("medusa", "Team B's"));
			count++;
		}
		else if (choice == 5)
		{
			bLineup.push(new HarryPotter("harrypotter", "Team B's"));
			count++;
		}
		else
			cout << "Invalid choice...";

	} while (count < numHeros);
}

/*********************************************************************
** Function: Tournament::play
**
** Description: The main play loop for the tournament. First the 
** starting team lineups are displayed, then the loop begins. The loop 
** consists of the following: check each team to make sure they still
** have heros remaining in their lineup. If they do, create a new 
** combat object using the first hero in each lineup and run the combat
** play loop. Then update each players lineup and the loser pile, 
** depending on which team won the round. When a team runs out of heros,
** the declareWinner function determines and displays the winner and the
** user is asked if they want to view the loser pile before returning
** to the main menu.
**
** Return: Displays the starting lineup, the results of each round, 
** the results of the tournament, and a prompt to ask the user whether 
** or not they want to view the loser pile. 
*********************************************************************/
void Tournament::play()
{
	bool winnerDeclared = false;
	int count = 1; //the current round
	cout << endl;

	//first display the starting lineup
	cout << "STARTING LINEUPS" << endl;
	cout << "Team A:" << endl;
	aLineup.print();
	cout << endl;
	cout << "Team B:" << endl;
	bLineup.print();
	cout << endl;

	//run the following tournament play loop until a winner is declared
	do
	{
		//first check to see if one player is out of heros, if so end the game loop
		if (aElements == 0 || bElements == 0)
			winnerDeclared = true;
		else
		{
			//get the first heros in each teams lineup
			Hero* playerOne = aLineup.getHead();
			Hero* playerTwo = bLineup.getHead();

			//begin the round by creating a new combat object and running the play function
			cout << "***ROUND " << count << "***" << endl;
			Combat round(playerOne, playerTwo);
			round.play();

			//if team A wins, alter the line-ups accordingly and add a point to team A
			if (round.getWinner() == "Team A")
			{
				aLineup.push(playerOne);   //push the winning hero to the back of the line-up
				aLineup.pop();             //pop the winning hero off the front of the line-up
				loserPile.push(playerTwo); //push the losing hero to the loser pile
				bLineup.pop();             //pop the losing hero from the line-up
				bElements--;               //decrease the number of heros on the losing team
				aPoints++;                 //give the winning team a point
			}
			//if team B wins, alter the line-ups accordingly and add a point to team B
			else
			{
				bLineup.push(playerTwo);   //push the winning hero to the back of the line-up
				bLineup.pop();             //pop the winning hero off the front of the line-up
				loserPile.push(playerOne); //push the losing hero to the loser pile
				aLineup.pop();             //pop the losing hero from the line-up
				aElements--;               //decrease the number of heros on the losing team
				bPoints++;                 //give the winning team a point
			}
			count++;
		}
	} while (!winnerDeclared);

	//notify the user of the winner
	declareWinner();

	//ask the user if they would like to see the loser pile
	cout << endl;
	cout << "**********************************" << endl;
	cout << "* What would you like to do?     *" << endl;
	cout << "*                                *" << endl;
	cout << "* 1. View the loser pile         *" << endl;
	cout << "* 2. Return to main menu         *" << endl;
	cout << "**********************************" << endl << endl;

	int choice = getInteger("Enter your choice:");

	//if the user wants to see the loser pile
	if (choice == 1)
	{
		cout << endl;
		cout << "LOSER PILE: " << endl;
		//pop each member of the loser pile and cout the character name
		loserPile.print();
		cout << endl;
	}
	//if the user didn't opt to see the loser pile, free all of loser pile items
	else
	{
		//determine the number of elements in the loser pile
		int elements = (2 * numHeros) - (aElements + bElements);

		for (int i = 0; i < elements; i++)
			loserPile.pop();
	}

	//free the memory allocated for each teams lineup
	for (int i = 0; i < aElements; i++)
		aLineup.pop();

	for (int i = 0; i < bElements; i++)
		bLineup.pop();
}

/*********************************************************************
** Function: Tournament::declarWinner
**
** Description: Determines the winner of the tournament by comparing
** team A's points to team B's points. Then the winner and final score
** is displayed.
**
** Return: Prints the winner and final scores to the screen.
*********************************************************************/
void Tournament::declareWinner()
{
	//notify the user of the tournament winner
	if (aPoints > bPoints)
	{
		cout << endl;
		cout << "TEAM A WINS THE TOURNAMENT!!!" << endl;
		cout << "     Team A's Final Score: " << aPoints << endl;
		cout << "     Team B's Final Score: " << bPoints << endl;
	}
	else if (bPoints > aPoints)
	{
		cout << endl;
		cout << "TEAM B WINS THE TOURNAMENT!!!" << endl;
		cout << "     Team A's Final Score: " << aPoints << endl;
		cout << "     Team B's Final Score: " << bPoints << endl;
	}
}

/*********************************************************************
** Function: Tournament::getInteger
**
** Description: Input validation function for integers.
**
** Parameters: A single string, which is the prompt that asks the user
** for a specific input.
**
** Return: Returns an integer which has been verified to be a
** non-negative and non-zero integer.
*********************************************************************/
int Tournament::getInteger(std::string prompt)
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