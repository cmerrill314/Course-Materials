/* Queue.hpp is the Queue class specification file.*/

#include <iostream>
using namespace std;

//include guards
#ifndef QUEUE_HPP 
#define QUEUE_HPP

class Queue
{
protected:
	struct queueList
	{
		int value; 
		queueList* next;
		queueList* prev;

		//struct constructor
		queueList(int val)
		{
			value = val;
			next = NULL;
		}
	};

	queueList* head; //the beginning of the linked list
	queueList* tail; //the end of the linked list
	queueList* node; //used to add items to the list

public:
	Queue();         //constructor
	~Queue();        //destructor
	int pop();       //removed the "top" item from the list
	void push(int);  //adds an item to the list
	void print();    //displays the list
};

#endif