/*********************************************************************
** Author: Christopher Merrill
** Date: 10/1/2016
** Description: This program performs an insertion sort on each line
** of a file data.txt. The first value on each line of data.txt 
** is the n-value (the number of items to be sorted). After each line
** is sorted, it is written to an output file insert.out 
*********************************************************************/

#include <vector>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

//Function declarations
void merge(vector<int>& left, vector<int>& right, vector<int>& vals);
void mergeSort(vector<int>& vsls);

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
        
		//Perform Merge Sort on the vector
		mergeSort(values);
		
		//Calculate the runtime
		runtime = (clock() - start) / (double) CLOCKS_PER_SEC;
		cout << "INSERTION SORT RUNTIME FOR " << n << " VALUES: " << runtime << endl;
		
		//Increment count and double n-value
		count++;
		n *= 2;
	}
	
    return 0;
}

/************************************************************************************************
merge

Description: Merges two vectors into one sorted vector 
************************************************************************************************/
void merge(vector<int>& left, vector<int>& right, vector<int>& vals) {
    int leftLength = left.size();
    int rightLength = right.size();
    int i = 0, j = 0, k = 0;

	//While there are still values in the left and right vectors
    while (j < leftLength && k < rightLength) 
    {	
		//If the left vectors value is less than the right vectors, add it to 
		//the main vector and increment the left vector
        if (left[j] < right[k]) {
            vals[i] = left[j];
            j++;
        }
		//Otherwise add the value from the right vector to the main vector
        else {
            vals[i] = right[k];
            k++;
        }
		//Increment to the next value in the main vector
        i++;
    }
	
	//Add any leftover values from the left vector
    while (j < leftLength) {
        vals[i] = left[j];
        j++; 
		i++;
    }
	
	//Add any leftover values from the right vector
    while (k < rightLength) {
        vals[i] = right[k];
        k++; 
		i++;
    }
}

/************************************************************************************************
mergeSort

Description: Performs a merge sort on a passed array using recursion and the merge function above. 
************************************************************************************************/
void mergeSort(vector<int>& vals) {
	int mid = vals.size() / 2;
    vector<int> left;
    vector<int> right;
	
	//Only perform mergeSort if the vector has 2 or more values
    if (vals.size() > 1){
		
		//Split the vector into left and right vectors
		for (int j = 0; j < mid; j++) {
			left.push_back(vals[j]);
		}
			
		for (int j = 0; j < (vals.size()) - mid; j++) {
			right.push_back(vals[mid + j]);
		}
		
		//Recursive step
		mergeSort(left);
		mergeSort(right);
		
		//Merge the sorted vectors
		merge(left, right, vals);
	}
}