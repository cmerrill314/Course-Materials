/* Medusa.hpp is the Medusa class specification file.*/

#include "Hero.hpp"

//include guard
#ifndef MEDUSA_HPP 
#define MEDUSA_HPP

class Medusa : public Hero
{
public:
	Medusa(std::string value, std::string team) : Hero(value, team) {}; //default constructor
	int attack();    //medusa specific attack function
	int defend(int); //medusa specific defend function
};

#endif