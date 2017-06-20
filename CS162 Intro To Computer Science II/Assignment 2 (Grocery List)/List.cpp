#include "List.hpp"
#include <iostream> 
using std::cout;
using std::endl;

//constructor definition
List::List()
{
	list = new Item*[4]; //inialize the dynamic array to hold four Items
	size = 0;            //initialize list size to 0.
	grandTotal = 0;      //initialize grand total to 0.
	listSize = 4;        //the list can hold four elements when created
}

/*********************************************************************
**                        List::operator==
**
*********************************************************************/
bool operator==(Item a, Item b)
{
	return a.getName() == b.getName();
}

/*********************************************************************
**                        List::addItem
** 
*********************************************************************/
void List::addItem(std::string name, std::string unit, int quantity, double price)
{
	//if there is more than one item in the list, check for a duplicate entry
	if (size >= 1)
	{
		bool duplicate = true;

		//check to see if the new Item is equal to any old items using the overloaded == operator
		for (int i = 0; i < size; i++)
		{
			if (list[i]->getName() == name)
				duplicate = false;
		}

		if (!duplicate)
			cout << "That item already exists." << endl << endl;
		else
		{
			//create a new list Item and update size and grand total
			list[size] = new Item(name, unit, quantity, price);
			grandTotal += list[size]->getExtendedPrice();
			size += 1;
		}
	}
	else
	{
		//create a new list Item and update size and grand total
		list[size] = new Item(name, unit, quantity, price);
		grandTotal += list[size]->getExtendedPrice();
		size += 1;
	}
}

/*********************************************************************
**                        List::removeItem
**
*********************************************************************/
void List::removeItem(std::string name)
{
	int validate = 0; //decides if the inputted name is valid (1 = valid, 0 = invalid)

	//if the list has no items, notify the user and go back to the main menu
	if (size == 0)
	{
		cout << "There are no items to remove." << endl << endl;
		return;
	}

	//check if the item name exists in the list
	for (int i = 0; i < size; i++)
	{
		if (name == list[i]->getName())
			validate += 1;
	}

	//create a temporary array to hold the items that will remain in the list after removal
	Item** temp = new Item*[size];
	int tempSize = 0;

	//if the entered name was valid, continue with removal
	if (validate == 1)
	{
		//add every element, besides the one being removed, to the temporary array
		for (int i = 0; i < size; i++)
		{
			if (name != list[i]->getName())
			{
				temp[tempSize] = new Item(list[i]->getName(), list[i]->getUnit(), list[i]->getQuantity(), list[i]->getUnitPrice());
				tempSize++;
			}
			else
			{
				//subtract the extended price of the removed item to from the grand total
				grandTotal -= list[i]->getExtendedPrice();
			}
		}

		//decrement the list size
		size -= 1;

		//set list equal to temp
		list = temp;
	}
	//if the entered name was invalid, notify the user and go back to the main menu
	else
		cout << "Item not found..." << endl << endl;
}

/*********************************************************************
**                        List::allocate
**
*********************************************************************/
void List::allocate()
{
	if (size == listSize)
	{
		//create a temporary array with 4 extra memory slots to hold the Items in the list
		Item** temp = new Item*[size+4];

		//read the items from list into the temporary array
		for (int i = 0; i < size; i++)
		{
			temp[i] = new Item(list[i]->getName(), list[i]->getUnit(), list[i]->getQuantity(), list[i]->getUnitPrice());
		}

		//set list equal to temp
		list = temp;
	}
}

/*********************************************************************
**                        List::getGrandTotal
**
*********************************************************************/
double List::getGrandTotal()
{
	return grandTotal;
}

/*********************************************************************
**                        List::printList
**
*********************************************************************/
void List::printList()
{
	for (int i = 0; i < size; i++)
	{
		Item* item = list[i];
		item->print();
	}
}