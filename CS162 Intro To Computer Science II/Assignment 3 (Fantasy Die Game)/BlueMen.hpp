/* BlueMen.hpp is the BlueMen class specification file.*/

#include "Hero.hpp"

//include guard
#ifndef BLUEMEN_HPP 
#define BLUEMEN_HPP

class BlueMen : public Hero
{
public:
	BlueMen(std::string value) : Hero(value) {}; //default constructor
	int attack();    //blue men specific attack function
	int defend(int); //blue men specific defend function
};

#endif
