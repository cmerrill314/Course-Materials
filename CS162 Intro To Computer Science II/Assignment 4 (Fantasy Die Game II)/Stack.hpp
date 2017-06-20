/* Stack.hpp is the Stack class specification file.*/

#include "Hero.hpp"

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
		Hero* value;
		stackList* next;

		//struct constructor
		stackList(Hero* val)
		{
			value = val;
			next = NULL;
		}
	};

	stackList* head; //the beginning of the linked list
	int elements;

public:
	Stack() { head = NULL; elements = 0; }; //constructor
	~Stack();                 //destructor
	Hero* pop();              //removed the "top" item from the list
	std::string getEndTeam(); //returns the team of the last value of the list
	void push(Hero*);         //adds an item to the list
	void print();             //displays the list
};

#endif