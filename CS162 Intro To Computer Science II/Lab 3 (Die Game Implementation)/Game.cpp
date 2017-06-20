#include "Game.hpp"
#include <iostream>
using namespace std;

//contructor definition
Game::Game(std::string one, std::string two, int rounds)
{
	playerOne = one;      //decides if player one's die is loaded/unloaded
	playerTwo = two;      //decides if player one's die is loaded/unloaded
	totalRounds = rounds; //total number of rounds in the game

	currentRound = 1;     //initialize current round to 1
	playerOneScore = 0;   //initialize score to 0
	playerTwoScore = 0;   //initialize score to 0
}

/*********************************************************************
**                            Game::play
** This is the main play loop for the dice game. It consists of four 
** options: Both players have unloaded die, both players have loaded
** die, Player One has a loaded die and Player Two has an unloaded die,
** or Player Two has a loaded die and Player One has an unloaded die. 
** The function takes two integers as input, corresponding to the 
** number of sides on Player One/Player Two's die. Within each option 
** the same game loop takes place: Each players die are created, the
** die are "rolled" for the specified number of rounds, and finally
** the results are printed. 
*********************************************************************/
void Game::play(int one, int two)
{
	//OPTION 1: Both players have loaded die
	if (playerOne == "Loaded" && playerTwo == "Loaded")
	{
		//instantiate the die
		LoadedDie firstPlayer(one);
		LoadedDie secondPlayer(two);

		//main game loop. runs for the specified number of rounds
		do
		{
			//roll the die
			int rollOne = firstPlayer.loadedRoll();
			int rollTwo = secondPlayer.loadedRoll();

			//display each player's roll
			cout << endl;
			cout << "Round  " << currentRound << ":" << endl;
			cout << "Player One's Roll: " << rollOne << endl;
			cout << "Player Two's Roll: " << rollTwo << endl;

			//display the results of the round
			if (rollOne > rollTwo)
			{
				cout << "Player One Wins." << endl << endl;
				playerOneScore += 1; //increase player one's score
			}
			else if (rollOne < rollTwo)
			{
				cout << "Player Two Wins." << endl << endl;
				playerTwoScore += 1; //increase player two's score
			}
			else
			{
				cout << "Draw." << endl << endl;
			}

			//increment rounds
			currentRound += 1;

		} while (currentRound <= totalRounds);

		//display player score and die stats
		cout << "*********************************************************************" << endl;
		cout << "**                             RESULTS                             **" << endl;
		cout << "*********************************************************************" << endl << endl;
		cout << "Player One: " << endl;
		cout << "------------------" << endl;
		cout << "Die Type: " << playerOne << endl;
		cout << "Sides on Die: " << one << endl;
		cout << "Score: " << playerOneScore << " points" << endl << endl;
		cout << "Player Two: " << endl;
		cout << "------------------" << endl;
		cout << "Die Type: " << playerTwo << endl;
		cout << "Sides on Die: " << two << endl;
		cout << "Score: " << playerTwoScore << " points" << endl << endl;

		//display the winner
		if (playerOneScore > playerTwoScore)
		{
			cout << "PLAYER ONE WINS THE GAME!!!!" << endl << endl;
		}
		else if (playerOneScore < playerTwoScore)
		{
			cout << "PLAYER TWO WINS THE GAME!!!!" << endl << endl;
		}
		else
		{
			cout << "THE GAME WAS A DRAW..." << endl << endl;
		}
	}
	//OPTION 2: Player One has a loaded die and Player Two has an unloaded die
	else if (playerOne == "Loaded" && playerTwo == "Unloaded")
	{
		//instantiate the die
		LoadedDie firstPlayer(one);
		Die secondPlayer(two);

		//main game loop. runs for the specified number of rounds
		do
		{
			//roll the die
			int rollOne = firstPlayer.loadedRoll();
			int rollTwo = secondPlayer.roll();

			//display each player's roll
			cout << endl;
			cout << "Round  " << currentRound << ":"<< endl;
			cout << "Player One's Roll: " << rollOne << endl;
			cout << "Player Two's Roll: " << rollTwo << endl;

			//display the results of the round
			if (rollOne > rollTwo)
			{
				cout << "Player One Wins." << endl << endl;
				playerOneScore += 1; //increase player one's score
			}
			else if (rollOne < rollTwo)
			{
				cout << "Player Two Wins." << endl << endl;
				playerTwoScore += 1; //increase player two's score
			}
			else
			{
				cout << "Draw." << endl << endl;
			}

			//increment rounds
			currentRound += 1;

		} while (currentRound <= totalRounds);

		//display player score and die stats
		cout << "*********************************************************************" << endl;
		cout << "**                             RESULTS                             **" << endl;
		cout << "*********************************************************************" << endl << endl;
		cout << "Player One: " << endl;
		cout << "------------------" << endl;
		cout << "Die Type: " << playerOne << endl;
		cout << "Sides on Die: " << one << endl;
		cout << "Score: " << playerOneScore << " points" << endl << endl;
		cout << "Player Two: " << endl;
		cout << "------------------" << endl;
		cout << "Die Type: " << playerTwo << endl;
		cout << "Sides on Die: " << two << endl;
		cout << "Score: " << playerTwoScore << " points" << endl << endl;

		//display the winner
		if (playerOneScore > playerTwoScore)
		{
			cout << "PLAYER ONE WINS THE GAME!!!!" << endl << endl;
		}
		else if (playerOneScore < playerTwoScore)
		{
			cout << "PLAYER TWO WINS THE GAME!!!!" << endl << endl;
		}
		else
		{
			cout << "THE GAME WAS A DRAW..." << endl << endl;
		}
	}
	//OPTION 3: Player One has an unloaded die and Player Two has a loaded die
	else if (playerOne == "Unloaded" && playerTwo == "Loaded")
	{
		//instantiate the die
		Die firstPlayer(one);
		LoadedDie secondPlayer(two);

		//main game loop. runs for the specified number of rounds
		do
		{
			//roll the die
			int rollOne = firstPlayer.roll();
			int rollTwo = secondPlayer.loadedRoll();

			//display each player's roll
			cout << endl;
			cout << "Round  " << currentRound << ":" << endl;
			cout << "Player One's Roll: " << rollOne << endl;
			cout << "Player Two's Roll: " << rollTwo << endl;

			//display the results of the round
			if (rollOne > rollTwo)
			{
				cout << "Player One Wins." << endl << endl;
				playerOneScore += 1; //increase player one's score
			}
			else if (rollOne < rollTwo)
			{
				cout << "Player Two Wins." << endl << endl;
				playerTwoScore += 1; //increase player two's score
			}
			else
			{
				cout << "Draw." << endl << endl;
			}

			//increment rounds
			currentRound += 1;

		} while (currentRound <= totalRounds);

		//display player score and die stats
		cout << "*********************************************************************" << endl;
		cout << "**                             RESULTS                             **" << endl;
		cout << "*********************************************************************" << endl << endl;
		cout << "Player One: " << endl;
		cout << "------------------" << endl;
		cout << "Die Type: " << playerOne << endl;
		cout << "Sides on Die: " << one << endl;
		cout << "Score: " << playerOneScore << " points" << endl << endl;
		cout << "Player Two: " << endl;
		cout << "------------------" << endl;
		cout << "Die Type: " << playerTwo << endl;
		cout << "Sides on Die: " << two << endl;
		cout << "Score: " << playerTwoScore << " points" << endl << endl;

		//display the winner
		if (playerOneScore > playerTwoScore)
		{
			cout << "PLAYER ONE WINS THE GAME!!!!" << endl << endl;
		}
		else if (playerOneScore < playerTwoScore)
		{
			cout << "PLAYER TWO WINS THE GAME!!!!" << endl << endl;
		}
		else
		{
			cout << "THE GAME WAS A DRAW..." << endl << endl;
		}
	}
	//OPTION 1: Both players have unloaded die
	else
	{
		//instantiate the die
		Die firstPlayer(one);
		Die secondPlayer(two);

		//main game loop. runs for the specified number of rounds
		do
		{
			//roll the die
			int rollOne = firstPlayer.roll();
			int rollTwo = secondPlayer.roll();

			//display each player's roll
			cout << endl;
			cout << "Round  " << currentRound << ":" << endl;
			cout << "Player One's Roll: " << rollOne << endl;
			cout << "Player Two's Roll: " << rollTwo << endl;

			//display the results of the round
			if (rollOne > rollTwo)
			{
				cout << "Player One Wins." << endl << endl;
				playerOneScore += 1; //increase player one's score
			}
			else if (rollOne < rollTwo)
			{
				cout << "Player Two Wins." << endl << endl;
				playerTwoScore += 1; //increase player two's score
			}
			else
			{
				cout << "Draw." << endl << endl;
			}

			//increment rounds
			currentRound += 1;

		} while (currentRound <= totalRounds);

		//display player score and die stats
		cout << "*********************************************************************" << endl;
		cout << "**                             RESULTS                             **" << endl;
		cout << "*********************************************************************" << endl << endl;
		cout << "Player One: " << endl;
		cout << "------------------" << endl;
		cout << "Die Type: " << playerOne << endl;
		cout << "Sides on Die: " << one << endl;
		cout << "Score: " << playerOneScore << " points" << endl << endl;
		cout << "Player Two: " << endl;
		cout << "------------------" << endl;
		cout << "Die Type: " << playerTwo << endl;
		cout << "Sides on Die: " << two << endl;
		cout << "Score: " << playerTwoScore << " points" << endl << endl;

		//display the winner
		if (playerOneScore > playerTwoScore)
		{
			cout << "PLAYER ONE WINS THE GAME!!!!" << endl << endl;
		}
		else if (playerOneScore < playerTwoScore)
		{
			cout << "PLAYER TWO WINS THE GAME!!!!" << endl << endl;
		}
		else
		{
			cout << "THE GAME WAS A DRAW..." << endl << endl;
		}
	}
		
}