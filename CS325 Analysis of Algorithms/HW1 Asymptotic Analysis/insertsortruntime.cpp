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
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
using namespace std;

int main()
{
	vector<int> values; //A vector of vectors. The inner vectors are the lines in data.txt
	int i, j, key, row = 0; 
	int count = 0;
	int n = 100;
	clock_t start;
	double runtime;
	
	//Seed the random number generator
	srand(time(NULL));
	
	//Perform 5 rounds of insertion sort, doubling n each time
	while (count < 8) {
		//Add n values to the vector
		for (i = 0; i < n; i++) {
			//Generate a random value between 0 and 10,000
			values.push_back(rand() % 10001); 
		}
		
		//Start the clock
		start = clock();
        
		//Perform Insertion Sort on the vector
		for (i = 1; i < n; i++) {
			key = values[i];
			for(j = i - 1; (j >= 0) && (values[j] > key); j--) {
				values[j+1] = values[j];
			}
			values[j+1] = key;
		}
		
		//Calculate the runtime
		runtime = (clock() - start) / (double) CLOCKS_PER_SEC;
		
		cout << "INSERTION SORT RUNTIME FOR " << n << " VALUES: " << runtime << endl;
		
		//Increment count and double n-value
		count++;
		n *= 2;
	}
	
	
	
    return 0;
}