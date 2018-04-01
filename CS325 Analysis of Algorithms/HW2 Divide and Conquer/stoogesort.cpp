/*********************************************************************
** Author: Christopher Merrill
** Date: 10/1/2016
** Description: This program performs a STOOGESORT on each line
** of a file data.txt. The first value on each line of data.txt 
** is the n-value (the number of items to be sorted). After each line
** is sorted, it is written to an output file stooge.out 
*********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <ctgmath>
using namespace std;

//Function declaration
void stoogeSort(vector<int>& vals, int start, int end);

int main()
{
	ifstream inFile;              //Input file data.txt
	ofstream outFile;             //Output file stooge.out
	string line;                  //Holds a line of numbers from data.txt
	vector< vector<int> > values; //A vector of vectors. The inner vectors are the lines in data.txt
	int i, j, n, key, row = 0;    
	
	//Open the input/output files for reading and writing
	inFile.open("data.txt");
	outFile.open("stooge.out");
	
	//Check to make sure inFile is valid
	if (inFile) {	
		while (getline(inFile, line)) {
			//Push a line to the values vector
			istringstream is(line);
			values.push_back(vector<int>(istream_iterator<int>(is), istream_iterator<int>()));
			
			//Set n-value then remove it from the front of the vector
			n = values[row][0];	
			values[row].erase(values[row].begin());
				
			//Perform Merge Sort on row
			stoogeSort(values[row], 0, (n-1));
			
			//Write results to outFile
			for (i = 0; i < n; i++) {
				outFile << values[row][i] << ' ';
			}
			outFile << endl; //Add newline at end of row
			
			//Increment the row count
			row++;
		}
		//Close the input/output files
		outFile.close();
		inFile.close();
	}
	
    return 0;
}

/************************************************************************************************
stoogeSort

Description: Performs a STOOGESORT on a passed array using the recursive pseudocode provided in
the homework assignment. It sorts the first 2/3 of a vactor, then the final 2/3 and then the 
first 2/3 again on each iteration. 
************************************************************************************************/
void stoogeSort(vector<int>& vals, int start, int end) {
	int temp;
	int n = end - start + 1; //the total number of ints in the vector
	int m = ceil(2*n)/3;     //m is equal to the ceiling of (2/3) * n

	//Base Case
	if ((n == 2) && (vals[start] > vals[end])) {
		//Swap vals[start] and vals[end]
		temp = vals[start];
		vals[start] = vals[end];
		vals[end] = temp;
	}
	//When n>2
	else if (n > 2){
		temp = n/3; // Set temp eqaul to 1/3 of n
	
		//Recursive Step
		stoogeSort(vals, start, (end - temp)); //Sort the first 2/3 of the vector
		stoogeSort(vals, (start+temp), end);   //Sort the final 2/3 of the vector
		stoogeSort(vals, start, (end - temp)); //Sort the first 2/3 of the vector again		
	}
}