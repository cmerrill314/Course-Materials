#include "Item.hpp"

#include <iostream>
using std::cout;
using std::endl;

//constructor definition
Item::Item(std::string nm, std::string unt, int qnt, double prc)
{
	name = nm;
	unit = unt;
	quantity = qnt;
	unitPrice = prc;

	extendedPrice = qnt*prc;
}

/*********************************************************************
**                        Item::getExtendedCost
** 
*********************************************************************/
double Item::getExtendedPrice()
{
	return extendedPrice;
}

/*********************************************************************
**                        Item::getName
** 
*********************************************************************/
std::string Item::getName()
{
	return name;
}

/*********************************************************************
**                        Item::getUnit
**
*********************************************************************/
std::string Item::getUnit()
{
	return unit;
}

/*********************************************************************
**                        Item::getQuantity
**
*********************************************************************/
int Item::getQuantity()
{
	return quantity;
}

/*********************************************************************
**                        Item::getUnitPrice
**
*********************************************************************/
double Item::getUnitPrice()
{
	return unitPrice;
}

/*********************************************************************
**                        Item::print
** Prints an Item's corresponding information. Used when diplaying the 
** grocery list.
*********************************************************************/
void Item::print()
{
	cout << quantity << " " << unit << " " << name << " ($" << unitPrice << " per " << unit << ") TOTAL: $" << extendedPrice << endl;
}