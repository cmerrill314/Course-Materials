/* HarryPotter.hpp is the HarryPotter class specification file.*/

#include "Hero.hpp"

//include guard
#ifndef HARRYPOTTER_HPP 
#define HARRYPOTTER_HPP

class HarryPotter : public Hero
{
public:
	HarryPotter(std::string value) : Hero(value) {}; //default constructor
	int attack();    //harry potter specific attack function
	int defend(int); //harry potter specific defend function
};

#endif