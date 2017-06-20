#include "Queue.hpp"
#include <cstdlib> //required for rand() and srand()
#include <ctime>   //required to seed rand()

/*********************************************************************
** Function: Queue::Queue
**
** Description: Queue class constructor. Initializes all data members
** and seeds the random number generator.
**
** Parameters: Takes three ints as parameters. val1 represents the 
** number of turns the simulation will run, val2 represents the 
** probability that a umber will be added to the queueand val3 represents
** the probability that a number will be removed from the queue.
*********************************************************************/
Queue::Queue(int val1, int val2, int val3)
{
	totalTurns = val1;
	addChance = val2;
	removeChance = val3;
	num = 0;
	length = 0;

	//seed the random number generator
	srand(time(0));  
}

/*********************************************************************
** Function: Queue::generateNum
**
** Description: Generates a random number between 0-100 using rand(). 
** This random number has a user-specified probability of being added 
** to the queue. 
*********************************************************************/
void Queue::generateNum()
{
	num = rand() % 101;
}

/*********************************************************************
** Function: Queue::runSimulation
**
** Description: Runs the buffer simulation. First a random number is
** generated. Depending on the probabilities that the user specified 
** and the outcome of the random number generators, the number is added
** to the queue and/or a number is removed from the queue. 
**
** Return: Returns the average length of the buffer accross all turns. 
*********************************************************************/
int Queue::runSimulation()
{
	//generate a random number to add to the queue
	generateNum();

	//run the following loop for the user-specified number of turns
	for (int i = 0; i < totalTurns; i++)
	{
		int num1 = rand() % 101; //add value probability
		int num2 = rand() % 101; //remove value probability
		
		//add a value to the buffer if the probability permits
		if (num1 <= addChance)
			buffer.push(num);

		//remove a value from the buffer if the probability permits
		if (num2 <= removeChance)
		{
			//only remove if the buffer isn't empty
			if (buffer.size() != 0)
				buffer.pop();
		}
			
		generateNum(); //generate a new number to add next round
		length += buffer.size(); //add the current buffer length to
								 //the total length (for calculating
								 //the average)
	}

	//return the average length of the buffer
	return (length / totalTurns);
}