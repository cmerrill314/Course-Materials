/* Hero.hpp is the Hero class specification file.*/

#include <string>

//include guard
#ifndef HERO_HPP 
#define HERO_HPP

class Hero
{
protected:
	std::string name; //hero's name
	int armor;        //hero's armor value
	int strength;     //hero's current strength
	int atkDieSides;  //number of sides on a hero's attack die
	int defDieSides;  //number of sides on a hero's defense die
	bool powerEnacted; //whether or not a hero's power has been enacted
	std::string powerText; //text displayed when a power is enacted
	std::string powerTextTwo; //secondary text displayed when a power is enacted
	bool hogwartsUsed; //whether or not hogwarts power has been used

public:
	Hero(); //default constructor
	Hero(std::string);  //constructor
	
	virtual int attack() = 0;    //pure virtual attack function for hero types
	virtual int defend(int) = 0; //pure virtual defend function for hero types
	
	std::string getName() { return name; }; //returns a hero's name
	int getStrength() { return strength; }; //returns a hero's strength
	bool getPowerEnacted() { return powerEnacted; }; //returns whether or not a hero's power has been enacted
	std::string getPowerText() { return powerText; };//returns a hero's power text
	std::string getPowerTextTwo() { return powerTextTwo; }; //returns a hero's secondary power text
	void setPowerEnacted(bool value) { powerEnacted = value; }; //sets a hero's power enacted value
};

#endif