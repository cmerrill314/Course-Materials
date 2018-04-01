/*********************************************************************
Author: Christopher Merrill
Date: 10/11/2016

Description: 
This program used the makeChange function to find the 
minimum number of coins necessary to make change for a particular
value. The coind denominations are read in from one line of a file
called amount.txt, and the value to make change for is read in from
the next line. The results are then sent to an output file, 
change.txt, which has the following format:

COIN DENOMINATIONS: 1 5 9 11 25 
TARGET VALUE:       65
COINS USED:         1 1 1 0 2 
MINIMUM # OF COINS: 5
*********************************************************************/

#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <climits>
using namespace std;

//Function declaration
void makeChange(vector<int>& coins, int n, int val, ofstream& file);

int main()
{
	ifstream inFile;            //Input file amount.txt
	ofstream outFile;           //Output file change.txt
	string line;                //Holds a line from amount.txt
	vector< vector<int> > data; //A vector of vectors to hold lines from amount.txt
	int i, j, n, val, row = 0; 
	
	//Open the input/output files for reading and writing
	inFile.open("amount.txt");
	outFile.open("change.txt");
	
	//Check to make sure inFile is valid
	if (inFile) {	
		
		//Retrieve all lines of amount.txt and store them in the data vector
		while (getline(inFile, line)) {
			//Push lines to the data vector
			istringstream is(line);
			data.push_back(vector<int>(istream_iterator<int>(is), istream_iterator<int>()));
		}
		
		//Loop through each pair of lines in the data vector
		while (row < data.size()) {		
			//Set n-value to the number of coins in the first row of the pair
			n = data[row].size();				
			
			//Set val equal to the first val of the second row of the pair
			row++;
			val = data[row][0];
			
			//Write the original pair of lines to the outFile
			for (i = (row - 1); i <= row; i++) {
				for (j = 0; j < data[i].size(); j++) {
					outFile << data[i][j] << ' ';
				}
				outFile << endl; //Add newline at end of each row
			}
				
			//Run makeChange function on a pair of rows
			makeChange(data[row - 1], n, val, outFile);
			
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
makeChange

Description: 
This function takes a vector of n coins of increasing denominations and calculates the minimum
number of coins needed to make a passed value (val). The minimum number of coins needed and the 
denomination of those coins are then written to a passed output file. 

Inputs:
coins = A vector of coin values
n     = The number of different coins
val   = The value that we are trying to make change for
file  = The output file that the results will be printed to
************************************************************************************************/
void makeChange(vector<int>& coins, int n, int val, ofstream& file)
{
    int results[val + 1];      //Stores the min number of coins required for each value up to val+1
	int coinsUsed[val + 1][n]; //Stores the number of each denomination of coin used to reach the result
	int i, j, k, subResult;
 
    //Base case
    results[0] = 0;
 
    //Initialize all results values to be infinite
    for (i = 1; i <= val; i++) {
		results[i] = INT_MAX;
	}
       
	//Initialize all coinsUsed values to be 0
	for (i = 0; i <= val; i++) {
		for (j = 0; j < n; j++) {
			coinsUsed[i][j] = 0;
		}
	}
 
    //Determine the min coins required for all values from 1 to val
    for (i = 1; i <= val; i++) {
        //Loop through all coins smaller than i
        for (j = 0; j < n; j++) {
			//Check if the coin value is less than val
			if (coins[j] <= i) {	
				//subResult will hold the result of the current value minus the denomination of coins[j]
				subResult = results[i-coins[j]]; 
				//If subResult is not infinity, and provides a result with less coins than the current
				//result, add it to the results table
				if (subResult != INT_MAX && subResult + 1 < results[i]) {
					//Update results table
					results[i] = subResult + 1;
					//Copy existing coin counts from i - coins[j]
					for (k = 0; k < n; k++) {
						coinsUsed[i][k] = coinsUsed[i - coins[j]][k];
					}
					//Increment the coinsUsed array for the current coin j
					coinsUsed[i][j]++;
				}
			}
		}
    }
	
	//Add coinsUsed[val] to file
	for (i = 0; i < n; i++) {
		file << coinsUsed[val][i] << ' ';
	}
	file << endl;
	
	//Add minimum number of coins to file
	file << results[val] << endl;
}