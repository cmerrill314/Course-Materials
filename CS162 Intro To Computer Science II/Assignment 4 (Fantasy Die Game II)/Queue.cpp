#include "Queue.hpp"

/*********************************************************************
** Function: Queue::Queue
**
** Description: Constructor for the Queue class. head and tail are 
** initialized to NULL.
*********************************************************************/
Queue::Queue()
{
	head = NULL;
	tail = NULL;
}

/*********************************************************************
** Function: Queue::~Queue
**
** Description: Destructor for the Queue class. It loops through each
** item in the list and deletes it.
*********************************************************************/
Queue::~Queue()
{
	queueList* node = head;
	while (node != NULL)
	{
		queueList* temp = node;
		node = node->next;
		delete temp;
	}
}

/*********************************************************************
** Function: Queue::push
**
** Description: Adds an item to the end of the list.
**
** Parameters: Takes a pointer to a hero as an argument, which the user
** will specify.This hero will be added to the list.
*********************************************************************/
void Queue::push(Hero* val)
{
	//if this is the first item in the list, set head/tail equal to the new item
	if (head == NULL)
	{
		node = new queueList(val);
		node->prev = NULL;
		head = node;
		tail = node;
	}
	//otherwise find the end of the list and add the value there
	else
	{
		queueList* lastNode = head;
		//start at the top of the list and loop through until the end is found
		while (lastNode->next != NULL)
		{
			lastNode = lastNode->next;
		}
		//create the new node
		lastNode->next = new queueList(val);
		//update previous node and tail pointer
		lastNode->next->prev = lastNode;
		tail = lastNode->next;
	}
}

/*********************************************************************
** Function: Queue::pop
**
** Description: Removes the first item entered into the list. (FIFO)
**
** Return: Returns a pointer to the hero that was removed from the list.
*********************************************************************/
Hero* Queue::pop()
{
	//if the list is empty, notify the user and return NULL
	if (!head)
	{
		cout << "ERROR: Unable to pop, the list is empty." << endl;
		return NULL;
	}

	//do the following if there is only one item in the list
	if (tail->prev == NULL)
	{
		Hero* tailValue = tail->value;
		delete tail;
		tail = NULL;
		head = NULL;
		return tailValue;
	}

	queueList* firstNode = tail;
	queueList* secondNode;
	//start at the back of the list and loop through until the front is found
	while (firstNode->prev != NULL)
	{
		secondNode = firstNode;
		firstNode = firstNode->prev;
	}

	//store the value of the first list member, then delete it
	Hero* firstNodeValue = firstNode->value;
	delete firstNode;

	//update pointers
	head = secondNode;
	secondNode->prev = NULL;


	return firstNodeValue;
}

/*********************************************************************
** Function: Queue::print
**
** Description: Displays the heroes that are currently in the list.
*********************************************************************/
void Queue::print()
{
	int count = 1;

	queueList* node = head;
	while (node)
	{
		cout << node->value->getName() << endl;
		node = node->next;
		count++;
	}
}

