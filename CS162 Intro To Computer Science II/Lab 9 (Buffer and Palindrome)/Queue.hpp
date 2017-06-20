/* Queue.hpp is the Queue class specification file.*/
#include <queue>
#include <iostream>
using namespace std;

//include guards
#ifndef QUEUE_HPP 
#define QUEUE_HPP

class Queue
{
private:
	int totalTurns;  //the number of turns
	int addChance;   //the probability of adding a number
	int removeChance;//the probability of removing a number
	int num;         //the random-generated number to add
	int length;      //holds the length of the buffer after each turn

	queue<int> buffer; //STL queue container

public:
	Queue(int,int,int);   //constructor
	void generateNum();   //generates a random number
	int runSimulation();  //runs the simulation
};

#endif