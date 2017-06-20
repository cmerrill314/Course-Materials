#include "Stack.hpp"

/*********************************************************************
** Function: Stack::createPal
**
** Description: Turns a user-entered string into a palindrome. Utilizes
** a stack container from the STL to store the contents of the 
** palindrome then reads them into a string variable. 
**
** Return: Returns the palindrome as a string
*********************************************************************/
std::string Stack::createPal()
{
	int count = 0;
	char letter = word[count];

	//if the user entered an empty string, display an error
	if (letter == '\0')
	{
		cout << "ERROR: You entered an empty string, ";
		cout << "can't create a palindrome." << endl;

		return "";
	}
	else
	{
		std::string palindrome;

		//add each letter of the string to the stack 
		while (letter != '\0')
		{
			pal.push(letter);
			count++;
			letter = word[count];
		}

		//add each letter of the string to the stack in reverse order
		for (int i = count; i >= 0; i--)
		{
			pal.push(word[i]);
		}

		int size = pal.size();

		//pop each item in the stack after pushing it to the palindrome 
		//string
		for (int i = 0; i < size; i++)
		{
			palindrome.push_back(pal.top());
			pal.pop();
		}

		return palindrome;
	}
}