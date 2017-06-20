/* Vampire.hpp is the Vampire class specification file.*/

#include "Hero.hpp"

//include guard
#ifndef VAMPIRE_HPP 
#define VAMPIRE_HPP

class Vampire: public Hero
{
public:
	Vampire(std::string value) : Hero(value) {}; //default constructor
	int attack();     //vampire-specific attack function
	int defend(int);  //vampire-specific defense function
};

#endif