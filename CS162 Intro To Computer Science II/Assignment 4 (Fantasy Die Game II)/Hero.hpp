/* Hero.hpp is the Hero class specification file.*/

#include <string>

//include guard
#ifndef HERO_HPP 
#define HERO_HPP

class Hero
{
protected:
	std::string name; //hero's name
	std::string team; //hero's team
	int armor;        //hero's armor value
	int strength;     //hero's current strength
	int atkDieSides;  //number of sides on a hero's attack die
	int defDieSides;  //number of sides on a hero's defense die
	bool powerEnacted; //whether or not a hero's power has been enacted
	bool hogwartsUsed; //whether or not hogwarts power has been used

public:
	Hero(); //default constructor
	Hero(std::string, std::string);  //constructor
	
	virtual int attack() = 0;    //pure virtual attack function for hero types
	virtual int defend(int) = 0; //pure virtual defend function for hero types
	
	std::string getName() { return name; }; //returns a hero's name
	std::string getTeam() { return team; }; //return a hero's team
	int getStrength() { return strength; }; //returns a hero's strength
	int setStrength(int value) { strength = value; }; //sets a hero's strength value 
	bool getPowerEnacted() { return powerEnacted; }; //returns whether or not a hero's power has been enacted
	void setPowerEnacted(bool value) { powerEnacted = value; }; //sets a hero's power enacted value
	void setHogwartsUsed(bool value) { hogwartsUsed = value; }; //sets a hero's hogwarts used value
};

#endif