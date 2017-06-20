/* Item.hpp is the Item class specification file.*/

#include <string>

#ifndef ITEM_HPP 
#define ITEM_HPP

class Item
{
private:
	std::string name;     //item name
	std::string unit;     //unit of measurement (can, box, pound, etc.)
	int quantity;         //amount of item
	double unitPrice;     //price per unit
	double extendedPrice; //price per unit times the quantity of the unit
public:
	Item(std::string,std::string,int,double); //constructor
	double getExtendedPrice();                //retrieves the extended price
	std::string getName();                    //retrieves the item name    
	std::string getUnit();                    //retrieves the item unit 
	int getQuantity();
	double getUnitPrice();
	void print();                             //prints the item information
};

#endif