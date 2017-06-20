/* Stack.hpp is the Stack class specification file.*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

//include guards
#ifndef STACK_HPP 
#define STACK_HPP

class Stack
{
private:
	std::string word; //stores the user-entered string
	stack< char, vector<char> > pal; //STL stack container:
									 //holds the contents of the palindrome
public:
	Stack(std::string val) { word = val; }; //constructor
	std::string createPal(); //creates and returns a palindrome
};

#endif