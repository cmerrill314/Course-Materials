/*********************************************************************
** Program Filename: lab4.cpp
** Author: Christopher Merrill
** Date: 10/23/2016
**
** Description: This program consists of three recursive
** functions: The first takes in a string and returns the reverse of
** that string, the returns the sum of all of the values in an array,
** and the third returns the triangular number for an integer N.
**
** Input: The user inputs the menu option they want to carry out. For 
** the string reversal function, a string is inputted. For the array sum 
** function, the numbers in the array are read in by the user. For the
** tringlular number function, the user enters an integer N. 
**
** Output: String reversal: Outputs a string which is the reverse of 
** the entered string. Array Sum: Outputs the sum of the entered array
** values. Traingular number: Outputs the triangular number of the 
** entered integer. 
*********************************************************************/

#include <iostream>
#include  <string>
using std::cin;
using std::cout;
using std::endl;
using std::getline;

std::string stringReverse(std::string);
int arraySum(int[], int);
int triangularNumber(int);
int getInteger(std::string);

int main()
{
	int choice; //holds the user-entered menu choice

	//run the menu loop until the user decides to exit (option 4)
	do
	{
		cout << "*********************************************" << endl;
		cout << "*                    MENU                   *" << endl;
		cout << "*********************************************" << endl;
		cout << "* Which function would you like to execute? *" << endl;
		cout << "*                                           *" << endl;
		cout << "* 1. String Reversal                        *" << endl;
		cout << "* 2. Sum of an Array                        *" << endl;
		cout << "* 3. Triangular Number                      *" << endl;
		cout << "* 4. Exit                                   *" << endl;
		cout << "*                                           *" << endl;
		cout << "*********************************************" << endl << endl;

		//ask for the users selection with integer validation function
		choice = getInteger("What is your choice?");

		//if the user enters 1, run the string reversal function
		if (choice == 1)
		{
			std::string phrase;

			//ask for a string
			cout << "You have chosen String Reversal" << endl << endl;
			cout << "Enter a string:" << endl;
			cin.ignore();
			getline(cin, phrase);

			//display the reverse of the string
			cout << endl;
			cout << "The reverse of your string is: " << stringReverse(phrase) << endl << endl;
		}
		//if the user enters 2, run the array sum function
		else if (choice == 2)
		{
			int count = 0;
			int temp[100]; //temporarily holds the values that the user inputs 

			cout << endl;
			cout << "You have chosen Sum of an Array" << endl << endl;

			//ask the user to enter the elements of their array 
			cout << "Enter element " << count + 1 << " of your array (must be an integer). Or enter S to stop." << endl;

			//stop when S is entered (or any other non-integer value)
			while (cin >> temp[count])
			{
				count++;
				cout << "Enter element " << count + 1 << " of your array (must be an integer). Or enter S to stop." << endl;
			}

			//clear the flag caused by inputting S (or any other non integer value)
			cin.clear();
			cin.ignore();

			//create the user's array by copying values from the temporary array
			int numbers[count];
			for (int i = 0; i < count; i++)
			{
				numbers[i] = temp[i];
			}

			//print the user's array
			cout << endl;
			cout << "Your numbers are: [";
			for (int i = 0; i < count; i++)
			{
				if (i == (count - 1))
					cout << numbers[i];
				else
					cout << numbers[i] << ", ";
			}
			cout << "]" << endl << endl;

			//display the sum using the recursive function
			cout << "Sum: " << arraySum(numbers, count) << endl;
		}
		//if the user enters 3, run the triangular number function
		else if (choice == 3)
		{
			cout << "You have chosen Triangular Number" << endl << endl;
			//ask the user to input any integer
			int number = getInteger("Enter any integer:");
			//display the triangular number
			cout << endl;
			cout << "The triangular number of " << number << " is: " << triangularNumber(number) << endl << endl;
		}
		//if the user enters an invalid number, notify them and allow for another choice
		else if (choice != 4)
			cout << "Invalid choice. Please choose one of the menu options instead:" << endl << endl;

	} while (choice != 4);

	return 0;
}

/*********************************************************************
** Function: stringReverse
**
** Description: Recursively reverses a user-entered string.
** Parameters: A single string.
** Return: Returns a string which is the reverse of the user-entered 
** string.
*********************************************************************/
std::string stringReverse(std::string s)
{
	char lastLetter = s[s.length() - 1]; //stores the last letter of the string

	//base case
	if (s.length() <= 0){
		return "" + lastLetter;
	}
	else
	{
		//shorten the string by one letter
		s.erase(s.length() - 1); 
		return lastLetter + stringReverse(s);
	}
}

/*********************************************************************
** Function: arraySum
**
** Description: Recursively calculates the sum of a user-entered array.
** Parameters: An integer array and the number of elements in that array.
** Return: Returns the sum of the array that was included in the 
** parameters.
*********************************************************************/
int arraySum(int ary[], int elements)
{
	//base case
	if (elements < 0)
		return 0;
	else
		return ary[elements-1] + arraySum(ary, elements - 1);
}

/*********************************************************************
** Function: triangularNumber
**
** Description: Recursively calculates the triangular number for a given 
** integer.
** Parameters: A single integer. 
** Return: Returns the triangular number of the integer provided in the 
** parameters. 
*********************************************************************/
int triangularNumber(int num)
{
	//base case
	if (num == 0)
		return 0;
	else
		return num + triangularNumber(num - 1);
}

/*********************************************************************
** Function: getInteger
**
** Description: Input validation function for integers. 
** Parameters: A string prompt which notifies the user of the purpose of 
** the integer they should enter. 
** Return: Returns an integer after verifying that the entered value 
** is in fact an integer.
*********************************************************************/
int getInteger(std::string prompt)
{
	int num;

	//run the desired prompt
	cout << prompt << endl;
	cin >> num;

	//if the number entered was not an integer, prompt the user to try again
	while (!cin)
	{
		cout << "Invalid choice. Please enter an integer value instead." << endl;
		cin.clear();  //clear the error flag on cin
		cin.ignore(); //skip to the next new line
		cin >> num;
	}
	return num;
}