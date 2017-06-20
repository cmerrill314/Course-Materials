/*********************************************************************
** Program Filename: search
** Author: Christopher Merrill
** Date: 11/12/2016
**
** Description: Lab 7. This program runs various search/sort functions from 
** this week's lecture slides. The user decides which function to run
** and the results are displayed accordingly. 
**
** Input: The user decides if they want to run a linear search, binary 
** search or bubble sort function. If they choose linear search or 
** bubble sort, they will also input which file they want to use. 
**
** Output: In the case of a search, the position of the target value
** is the output. In the case of a sort, the sorted list is the output
** as well as a user-named output file that contains the contents of the
** sorted list. 
*********************************************************************/

#include <fstream>  
#include <vector>
#include <iostream>
#include <string>   
using namespace std;

int linearSearch(vector<int>, int, int);
int binarySearch(vector<int>, int, int);
void bubbleSort(vector<int>&, int);
int getInteger(std::string); //input validation function

int main()
{
	int choice;

	do
	{
		cout << endl;
		cout << "***********************************************" << endl;
		cout << "*                    LAB 7                    *" << endl;
		cout << "***********************************************" << endl;
		cout << "*   What would you like to do?                *" << endl;
		cout << "*                                             *" << endl;
		cout << "*   1. Search for the target value (linear)   *" << endl;
		cout << "*   2. Search for the target value (binary)   *" << endl;
		cout << "*   3. Sort a set of values                   *" << endl;
		cout << "*   4. Exit                                   *" << endl;
		cout << "*                                             *" << endl;
		cout << "***********************************************" << endl << endl;

		//ask for the user's selection 
		choice = getInteger("Enter your choice: ");

		//if the user enters 1, perform a linear search on one of the specified files
		if (choice == 1)
		{
			ifstream inputFile; 
			string fileName;    
			int integer;
			vector<int> list;

				cout << endl;
				cout << "***********************************************" << endl;
				cout << "*               LINEAR SEARCH                 *" << endl;
				cout << "***********************************************" << endl;
				cout << "*   Which file would you like to use?         *" << endl;
				cout << "*                                             *" << endl;
				cout << "*   1. Early                                  *" << endl;
				cout << "*   2. Middle                                 *" << endl;
				cout << "*   3. Late                                   *" << endl;
				cout << "*                                             *" << endl;
				cout << "***********************************************" << endl << endl;

				//ask for the user's selection 
				int choiceTwo = getInteger("Enter your choice: ");

				//input validation
				while (choiceTwo < 1 || choiceTwo > 3)
				{
					choiceTwo = getInteger("Invalid choice, please enter an option from the table above:"); 
				}
				
				//input the specified file
				if (choiceTwo == 1)
					fileName = "early.txt";
				else if (choiceTwo == 2)
					fileName = "middle.txt";
				else if (choiceTwo == 3)
					fileName = "late.txt";

				inputFile.open(fileName.c_str());

				//if the file is valid, read in the values from the file and store them in a vector
				if (inputFile)
				{
					while (inputFile >> integer)
						list.push_back(integer);
				}
				else
					cout << "Could not access file..." << endl;

				//close the file
				inputFile.close();

				//display the contents of the file
				cout << endl;
				cout << "File contents: ";
				for (int i = 0; i < list.size(); i++)
					cout << list[i] << " ";
				
				cout << endl;
				cout << "Position:      0 1 2 3 4 5 6 7 8 9" << endl << endl;

				//run the linear search
				int result = linearSearch(list, list.size(), 0);

				//display the results
				if (result == -1)
					cout << "Target not found" << endl;
				else
					cout << "The target was found at position: " << result << endl;
		}
		//if the user enters 2, perform a binary search on the sorted file
		else if (choice == 2)
		{
			ifstream inputFile; 
			int integer;
			vector<int> list;

			//input the sorted file
			inputFile.open("sorted.txt");

			//if the file is valid, read in the values from the file and store them in a vector
			if (inputFile)
			{
				while (inputFile >> integer)
					list.push_back(integer);
			}
			else
				cout << "Could not access file..." << endl;

			//close the file
			inputFile.close();

			//display the contents of the file
			cout << endl;
			cout << "File contents: ";
			for (int i = 0; i < list.size(); i++)
				cout << list[i] << " ";

			cout << endl;
			cout << "Position:      0 1 2 3 4 5 6 7 8 9" << endl << endl;

			//run the binary search
			int result = binarySearch(list, list.size(), 0);

			//display the results
			if (result == -1)
				cout << "Target not found" << endl;
			else
				cout << "The target was found at position: " << result << endl;
		}
		//if the user enters 3, sort one of the specified files
		else if (choice == 3)
		{
			ifstream inputFile;  
			ofstream outputFile; 
			string fileName;
			int integer;
			vector<int> list;

			cout << endl;
			cout << "***********************************************" << endl;
			cout << "*                    SORT                     *" << endl;
			cout << "***********************************************" << endl;
			cout << "*   Which file would you like to sort?        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*   1. Early                                  *" << endl;
			cout << "*   2. Middle                                 *" << endl;
			cout << "*   3. Late                                   *" << endl;
			cout << "*                                             *" << endl;
			cout << "***********************************************" << endl << endl;

			//ask for the user's selection 
			int choiceTwo = getInteger("Enter your choice: ");

			//input validation
			while (choiceTwo < 1 || choiceTwo > 3)
			{
				choiceTwo = getInteger("Invalid choice, please enter an option from the table above:");
			}

			//input the specified file
			if (choiceTwo == 1)
				fileName = "early.txt";
			else if (choiceTwo == 2)
				fileName = "middle.txt";
			else if (choiceTwo == 3)
				fileName = "late.txt";

			inputFile.open(fileName.c_str());

			//if the file is valid, read in the values from the file and store them in a vector
			if (inputFile)
			{
				while (inputFile >> integer)
					list.push_back(integer);
			}
			else
				cout << "Could not access file..." << endl;

			//close the input file
			inputFile.close();

			//display the contents of the file
			cout << endl;
			cout << "File contents:   ";
			for (int i = 0; i < list.size(); i++)
				cout << list[i] << " ";

			//run the bubble sort function
			bubbleSort(list, list.size());

			//display the sorted contents
			cout << endl;
			cout << "Sorted contents: ";
			for (int i = 0; i < list.size(); i++)
				cout << list[i] << " ";
			cout << endl << endl;

			cout << "Choose a file name for your output file: ";
			cin.clear();
			cin.ignore();
			getline(cin, fileName);
			cout << endl;

			//open the output file, write the sorted values into it, then close it
			outputFile.open(fileName.c_str());
			for (int i = 0; i < list.size(); i++)
				outputFile << list[i];
			outputFile.close();
		}
		//if the user fails to enter a menu option, tell them to choose again
		else if (choice != 4)
			cout << "Invalid choice, please choose one of the menu options instead:";

	} while (choice != 4);

	return 0;
}

/*********************************************************************
** Function: linearSearch
**
** Description: This is the linear search function from the "Searching"
** lecture slides, on slide number 6.
**
** Parameters: A vector, the size of that vector and the target value
** (in this case the target value is always 0.
**
** Return: Returns the position of the target value. If no target value
** is found, -1 is returned.
*********************************************************************/
int linearSearch(vector<int> a, int size, int v)
{
	for (int i = 0; i < size; i++)
	{
		if (a[i] == v)
			return i;
	}
	return -1;
}

/*********************************************************************
** Function: binarySearch
**
** Description: This is the binaray search function from the "Searching"
** lecture slides, on slide number 11. 
**
** Parameters: A vector, the size of that vector and the target value
** (in this case the target value is always 0.
**
** Return: Returns the position of the target value. If no target value 
** is found, -1 is returned.
*********************************************************************/
int binarySearch(vector<int> a, int size, int v)
{
	int low = 0;
	int high = size - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		int diff = a[mid] - v;
		if (diff == 0) //a[mid] == v
			return mid;
		else if (diff < 0) //a[mid] < v
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

/*********************************************************************
** Function: bubbleSort
**
** Description: This bubble sort function came from the "Sort-Bubble"
** lecture slides, on slide number 5
**
** Parameters: A reference to a vector and the size of that vector. 
*********************************************************************/
void bubbleSort(vector<int>& a, int size)
{
	for (int i = (size - 1); i >= 0; i--)
	{
		for (int j = 1; j <= i; j++)
		{
			if (a[j - 1] > a[j])
			{
				//swap elements at j-1 and j
				int temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}
	}
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