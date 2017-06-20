/* Barbarian.hpp is the Barbarian class specification file.*/

#include "Hero.hpp"

//include guard
#ifndef BARBARIAN_HPP 
#define BARBARIAN_HPP

class Barbarian : public Hero
{
public:
	Barbarian(std::string value, std::string team) : Hero(value, team) {}; //default constructor
	int attack();    //barbarian specific attack function
	int defend(int); //barbarian specific defend function
};

#endif