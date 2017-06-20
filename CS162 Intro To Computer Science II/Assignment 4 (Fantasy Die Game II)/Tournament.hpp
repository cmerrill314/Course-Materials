/* Stack.hpp is the Stack class specification file.*/

#include "Combat.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

#include <iostream>
using namespace std;

//include guards
#ifndef TOURNAMENT_HPP 
#define TOURNAMENT_HPP

class Tournament
{
private:
	int numHeros;    //the number of heros that make up each team
	int aPoints;     //team A's points
	int bPoints;     //team B's points
	int aElements;   //the number of remaining heros in team a's lineup
	int bElements;   //the number of remaining heros in team b's lineup
	Queue aLineup;   //team A's lineup
	Queue bLineup;   //team B's lineup
	Stack loserPile; //the loser pile

public:
	Tournament(int); //constructor

	void play(); //runs the tournament play loop 
	void populate(); //populates each team's lineup
	void declareWinner(); //determines the tournament winner
	int getInteger(std::string); //intput validation
};

#endif