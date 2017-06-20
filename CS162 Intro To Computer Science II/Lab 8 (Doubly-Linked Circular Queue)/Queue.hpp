/* Queue.hpp is the Queue class specification file.*/

#include <iostream>
using namespace std;

//include guards
#ifndef QUEUE_HPP 
#define QUEUE_HPP

class Queue
{
protected:
	//QueueNode structure
	struct QueueNode
	{
		int value; //data member 
		QueueNode* next;
		QueueNode* prev;

		//struct constructor
		QueueNode(int val)
		{
			value = val;
		}
	};

	QueueNode* front; //first item in the queue
	QueueNode* back;  //last item in the queue

public:
	Queue();           //constructor
	~Queue();        //destructor

	void addBack(int); //puts a new item at the end of the queue or
					   //creates a new node to store the item if the queue is full
	int getFront();    //returns the value at the front of the queue
	int removeFront(); //removes the first item in the structure
};

#endif