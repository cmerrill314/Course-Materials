/* Stack.hpp is the Stack class specification file.*/

#include <iostream>
using namespace std;

//include guards
#ifndef STACK_HPP 
#define STACK_HPP

class Stack
{
protected:
	struct stackList
	{
		int value;
		stackList* next;

		//struct constructor
		stackList(int val)
		{
			value = val;
			next = NULL;
		}
	};

	stackList* head; //the beginning of the linked list

public:
	Stack() { head = NULL; }; //constructor
	~Stack();                 //destructor
	int pop();                //removed the "top" item from the list
	void push(int);           //adds an item to the list
	void print();             //displays the list
};

#endif