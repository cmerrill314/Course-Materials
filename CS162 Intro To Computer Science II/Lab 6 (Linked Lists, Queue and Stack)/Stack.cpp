#include "Stack.hpp"

/*********************************************************************
** Function: Stack::~Stack
**
** Description: Destructor for the Stack class. It loops through each 
** item in the list and deletes it. 
*********************************************************************/
Stack::~Stack()
{
	stackList* node = head;
	//start at the top of the list and loop through until the end is found
	while (node != NULL)
	{
		//delete each item
		stackList* temp = node;
		node = node->next;
		delete temp;
	}
}

/*********************************************************************
** Function: Stack::push
**
** Description: Adds an item to the end of the list.
**
** Parameters: Takes an int as an argument, which the user will specify.
** This int is the value that will be added to the list.
*********************************************************************/
void Stack::push(int val)
{
	//if this is the first item in the list, set head equal to this item
	if (head == NULL)
		head = new stackList(val);
	//otherwise find the end of the list and add the value there
	else
	{
		stackList* node = head;
		//start at the top of the list and loop through until the end is found
		while (node->next != NULL)
		{
			node = node->next;
		}
		//set the position after the last value equal to the new value
		node->next = new stackList(val);
	}
}

/*********************************************************************
** Function: Stack::pop
**
** Description: Removes the last item entered into the list.
**
** Return: Returns an integer which has been verified to be a
** non-negative and non-zero integer.
*********************************************************************/
int Stack::pop()
{
	//if the list is empty, notify the user and return 0
	if (!head)
	{
		cout << "ERROR: Unable to pop, the list is empty." << endl;
		return 0;
	}

	//if the list only has one item, return the value of head and delete it
	if (head->next == NULL)
	{
		int headValue = head->value;
		delete head;
		head = NULL;
		return headValue;
	}

	stackList* topNode = head;
	stackList* previousNode;

	//start at the top of the list and loop through until the end is found
	while (topNode->next != NULL)
	{
		previousNode = topNode;
		topNode = topNode->next;
	}

	//store the value of the last list member, then delete it
	int topNodeValue = topNode->value;
	delete topNode;

	//update pointers and return the result
	previousNode->next = NULL;
	return topNodeValue;
}

/*********************************************************************
** Function: Stack::print
**
** Description: Displays the integers that are currently in the list.
** (Not necessary per the lab instructions, but I found it useful for 
** troubleshooting and verifying results).
*********************************************************************/
void Stack::print()
{
	int count = 1;
	
	stackList* node = head;
	while (node)
	{
		cout << node->value << " ";
		node = node->next;
		count++;
	}
}