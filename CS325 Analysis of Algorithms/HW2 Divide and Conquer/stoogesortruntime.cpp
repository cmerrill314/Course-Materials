/*********************************************************************
** Author: Christopher Merrill
** Date: 10/1/2016
** Description: This program performs a STOOGESORT on each line
** of a file data.txt. The first value on each line of data.txt 
** is the n-value (the number of items to be sorted). 
*********************************************************************/

#include <vector>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctgmath>
using namespace std;

//Function declaration
void stoogeSort(vector<int>& vals, int start, int end);

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
        
		//Perform Stooge Sort on the vector
		stoogeSort(values, 0, (n-1));
		
		//Calculate the runtime
		runtime = (clock() - start) / (double) CLOCKS_PER_SEC;
		cout << "STOOGE SORT RUNTIME FOR " << n << " VALUES: " << runtime << endl;
		
		//Increment count and double n-value
		count++;
		n *= 2;
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