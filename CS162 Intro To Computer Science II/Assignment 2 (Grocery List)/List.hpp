/* List.hpp is the List class specification file.*/

#include "Item.hpp"

#ifndef LIST_HPP 
#define LIST_HPP

class List 
{
private:
	Item** list;        //a dynamic array of Items  
	int size;           //the number of Items in the list
	int listSize;       //the number of items the list can hold
	double grandTotal;  //the total cost of every Item on the list
public:
	List();                 //constructor
	bool operator==(std::string); //overloaded == operator 
	void addItem(std::string, std::string, int, double); //adds an Item to the list
	void removeItem(std::string);      //removes an Item from the list
	double getGrandTotal(); //returns the grand total of all items on the list.
	void printList();
	void allocate(); 
};

#endif
