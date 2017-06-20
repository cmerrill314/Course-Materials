/*********************************************************************
** Program Filename: Fibonacci
** Author: Christopher Merrill
** Date: 11/28/2016
**
** Description: Lab 10. This program is a comparison between iterative
** and recursive methods of determining a Fibonacci Number. It is clear
** for n>29 that the iterative method performs significantly better.
**
** NOTE: The accompanying files were taken from Joseph Arul at:
** https://www.codeproject.com/tips/109443/fibonacci-recursive-and-non-recursive-c
** They were modified to include the time taken to run each function,
** and the int values were changed to long long's to allow for higher
** values of n.
**
** Input: The user inputs which function (or both) they want to run. 
** They also decide a value for n, the desired Fibonacci Number.
**
** Output: The program outputs the desired Fibonacci Number, as well
** as the time it took to compute the number using each method.
*********************************************************************/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "FibonacciR.hpp"
#include "FibonacciNR.hpp"
using namespace std;

int getInteger(std::string); //input validation function

int main() {
	clock_t t1; //time to run the recursive function
	clock_t t2; //time to run the iterative function
	long long n;      
	int choice;
	
	do
	{
		cout << endl;
		cout << "*******************************************************" << endl;
		cout << "*                      MAIN MENU                      *" << endl;
		cout << "*******************************************************" << endl;
		cout << "*   What would you like to do?                        *" << endl;
		cout << "*                                                     *" << endl;
		cout << "*   1. Run both the recursive and iterative methods   *" << endl;
		cout << "*   2. Run the recursive method only                  *" << endl;
		cout << "*   3. Run the iterative method only                  *" << endl;
		cout << "*   4. Exit                                           *" << endl;
		cout << "*                                                     *" << endl;
		cout << "*******************************************************" << endl << endl;

		//ask for the user's selection 
		choice = getInteger("Enter your choice:");
		cout << endl;

		if (choice == 1)
		{
			//ask the user to input n
			n = getInteger("Enter a value for n:");
			cout << endl;
			cout << "Finding '" << n << "'th " << "Fibonacci Number...." << endl;

			//call the recursive function
			t1 = clock();
			cout << "Calling Recursive Fibonacci implementation" << endl;
			FibonacciR fr(n);
			fr.PrintFibonacci();
			t1 = clock() - t1;

			//call the iterative function
			t2 = clock();
			cout << "Calling Non-Recursive Fibonacci implementation" << endl;
			FibonacciNR fnr(n);
			fnr.PrintFibonacci();
			t2 = clock() - t2;

			//display time results
			cout << endl;
			cout << "TIME RESULTS:" << endl;
			cout << "The recursive method took " << (((float)t1) / CLOCKS_PER_SEC) << " secs" << endl;
			cout << "The iterative method took " << (((float)t2) / CLOCKS_PER_SEC) << " secs" << endl;
		}
		else if (choice == 2)
		{
			//ask the user to input n
			n = getInteger("Enter a value for n:");
			cout << endl;
			cout << "Finding '" << n << "'th " << "Fibonacci Number...." << endl;

			//call the recursive function
			t1 = clock();
			cout << "Calling Recursive Fibonacci implementation" << endl;
			FibonacciR fr(n);
			fr.PrintFibonacci();
			t1 = clock() - t1;

			//display time results
			cout << endl;
			cout << "TIME RESULTS:" << endl;
			cout << "The recursive method took " << (((float)t1) / CLOCKS_PER_SEC) << " secs" << endl;
		}
		else if (choice == 3)
		{
			//ask the user to input n
			n = getInteger("Enter a value for n:");
			cout << endl;
			cout << "Finding '" << n << "'th " << "Fibonacci Number...." << endl;

			//call the iterative function
			t2 = clock();
			cout << "Calling Non-Recursive Fibonacci implementation" << endl;
			FibonacciNR fnr(n);
			fnr.PrintFibonacci();
			t2 = clock() - t2;

			//display time results
			cout << endl;
			cout << "TIME RESULTS:" << endl;
			cout << "The iterative method took " << (((float)t2) / CLOCKS_PER_SEC) << " secs" << endl;
		}
		else if (choice != 4)
			cout << "Invalid choice, please choose one of the menu options instead:" << endl;
	} while (choice != 4);

	return 0;
}

/*********************************************************************
** Function: getInteger
**
** Description: Input validation function for integers.
**
** Parameters: A single string, which is the prompt that asks the user
** for a specific input.
**
** Return: Returns an integer which has been verified to be a
** non-negative and non-zero integer.
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