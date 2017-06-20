/* Hero.hpp is the Hero class specification file.*/

#include "Hero.hpp"
#include <string>

//include guard
#ifndef COMBAT_HPP 
#define COMBAT_HPP

class Combat
{
private:
	Hero* playerOne;  //player one's hero 
	Hero* playerTwo;  //player two's hero
	std::string playerOneText; //holds the string "Player One"
	std::string playerTwoText; //holds the string "Player Two"
public:
	Combat(int, int); //default constructor
	void play();      //runs the game logic
	void cleanUp();   //destroys the created heros
};

#endif