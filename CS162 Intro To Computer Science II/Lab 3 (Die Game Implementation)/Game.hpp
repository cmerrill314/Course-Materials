/* Game.hpp is the Game class specification file.*/

#include "Die.hpp"
#include "LoadedDie.hpp"
#include <string>

//include guards
#ifndef GAME_HPP 
#define GAME_HPP

class Game
{
private:
	std::string playerOne; //stores whether or not player one's die is loaded/unloaded
	std::string playerTwo; //stores whether or not player two's die is loaded/unloaded
	int totalRounds;       //total number of rounds in the game
	int currentRound;      //keeps track of the current round
	int playerOneScore;    //keeps track of platyer one's score
	int playerTwoScore;    //keeps track of player two's score
public:
	Game(std::string, std::string, int); //constructor
	void play(int,int);                  //main game loop
};

#endif