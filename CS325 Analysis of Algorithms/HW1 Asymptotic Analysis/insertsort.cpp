/*********************************************************************
** Author: Christopher Merrill
** Date: 10/1/2016
** Description: This program performs an insertion sort on each line
** of a file data.txt. The first value on each line of data.txt 
** is the n-value (the number of items to be sorted). After each line
** is sorted, it is written to an output file insert.out 
*********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
using namespace std;

int main()
{
	ifstream inFile;              //Input file data.txt
	ofstream outFile;             //Output file insert.out
	string line;                  //Holds a line of numbers from data.txt
	vector< vector<int> > values; //A vector of vectors. The inner vectors are the lines in data.txt
	int i, j, n, key, row = 0;    
	
	//Open the input/output files for reading and writing
	inFile.open("data.txt");
	outFile.open("insert.out");
	
	//Check to make sure inFile is valid
	if (inFile) {
		while (getline(inFile, line)) {
			//Push a line to the values vector
			istringstream is(line);
			values.push_back(vector<int>(istream_iterator<int>(is), istream_iterator<int>()));
			
			//Set n-value then remove it from the front of the vector
			n = values[row][0];	
			values[row].erase(values[row].begin());
			values[row].pop_back();
				
			//Perform Insertion Sort on row
			for (i = 1; i < n; i++) {
				key = values[row][i];
				for(j = i - 1; (j >= 0) && (values[row][j] > key); j--) {
					values[row][j+1] = values[row][j];
				}
				values[row][j+1] = key;
			}

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