#include "Queue.hpp"

/*********************************************************************
** Function: Queue::Queue
**
** Description: Constructor for the Queue class. A doubly-linked 
** circular structure is created, consisting of one empty node with 
** prev and next pointing back to itself. 
*********************************************************************/
Queue::Queue()
{
	QueueNode* node = new QueueNode(-1);
	front = node;
	back = node;
	node->next = back;
	node->prev = front;
}

/*********************************************************************
** Function: Queue::~Queue
**
** Description: Destructor for the Queue class. 
*********************************************************************/
Queue::~Queue()
{
	QueueNode* node = front;
	bool queueEnd = false;
	while (!queueEnd)
	{
		if (node == back)
		{
			queueEnd = true;
		}

		QueueNode* temp = node;
		node = node->next;
		delete temp;
	}
}

/*********************************************************************
** Function: Queue::addBack
**
** Description: Adds an item to the back of the queue. If the queue is 
** full, a new node will be created.
**
** Parameters: Takes an int as an argument, which the user will specify.
** This int is the value that will be added to the list.
*********************************************************************/
void Queue::addBack(int val)
{
	bool itemAdded = false;

	QueueNode* node = front;
	QueueNode* previousNode = back;

	while (!itemAdded)
	{
		//if the back node is full, create a new node and update pointers
		if (node->value != -1 && node->next == front)
		{
			//create a new node
			QueueNode* newNode = new QueueNode(val);
			//update pointers
			node->next = newNode;
			newNode->next = front;
			newNode->prev = node;
			back = newNode;
			front->prev = back; 
			itemAdded = true;
		}
		//if the back node is empty, change the value to the new value
		else if (node->value == -1)
		{
			node->value = val;
			itemAdded = true;
		}
		//otherwise check the next node in the queue
		else
		{
			QueueNode* previousNode = node;
			node = node->next;
		}
	}
}

/*********************************************************************
** Function: Queue::getFront
**
** Description: Returns the value at the front of the queue. If no 
** value is present, -1 will be returned.
*********************************************************************/
int Queue::getFront()
{
	return front->value;
}

/*********************************************************************
** Function: Queue::removeFront
**
** Description: Removes the first item in the QueueNode structure by 
** replacing its value with -1, then adjusts pointers if necessary
*********************************************************************/
int Queue::removeFront()
{
	int temp = front->value;
	
	//if there's only one item in the queue, simply change its value to -1
	if (front->next == back)
	{
		front->value = -1;
	}
	//otherwise change the value to -1 and adjust pointers accordingly
	else
	{
		front->value = -1;
		back = front;        //set the back to the old front value
		front = front->next; //set front to the new front value
	}

	//return the removed item
	return temp;
}
