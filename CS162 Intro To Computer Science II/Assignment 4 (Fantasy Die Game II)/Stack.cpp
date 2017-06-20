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
** Parameters: Takes a pointer to a hero as an argument, which the user 
** will specify.This hero will be added to the list.
*********************************************************************/
void Stack::push(Hero* val)
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

	elements++;
}

/*********************************************************************
** Function: Stack::pop
**
** Description: Removes the last item entered into the list.
**
** Return: Returns a pointer to the hero that was removed from the list.
*********************************************************************/
Hero* Stack::pop()
{
	//if the list is empty, notify the user and return NULL
	if (!head)
	{
		cout << "ERROR: Unable to pop, the list is empty." << endl;
		return NULL;
	}

	//if the list only has one item, return the value of head and delete it
	if (head->next == NULL)
	{
		Hero* headValue = head->value;
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
	Hero* topNodeValue = topNode->value;
	delete topNode;

	//update pointers and return the result
	previousNode->next = NULL;
	return topNodeValue;
}

/*********************************************************************
** Function: Stack::print
**
** Description: Displays the loser pile in the proper order. Both the 
** team name and character name are displayed. 
*********************************************************************/
void Stack::print()
{
	for (int i = 0; i < elements; i++)
	{
		//first find the top of the pile to display the proper team name
		stackList* topNode = head;
		while (topNode->next != NULL)
		{
			topNode = topNode->next;
		}
		cout << topNode->value->getTeam() << " ";

		//then pop the loserPile to remove the top element and display its name
		cout << pop()->getName() << endl;
	}
}