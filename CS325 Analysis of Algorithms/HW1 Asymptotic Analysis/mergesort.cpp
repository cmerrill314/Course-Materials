/*********************************************************************
** Author: Christopher Merrill
** Date: 10/1/2016
** Description: This program performs a merge sort on each line
** of a file data.txt. The first value on each line of data.txt 
** is the n-value (the number of items to be sorted). After each line
** is sorted, it is written to an output file merge.out 
*********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <cstdlib>
using namespace std;

//Function declarations
void merge(vector<int>& left, vector<int>& right, vector<int>& vals);
void mergeSort(vector<int>& vsls);

int main()
{
	ifstream inFile;              //Input file data.txt
	ofstream outFile;             //Output file merge.out
	string line;                  //Holds a line of numbers from data.txt
	vector< vector<int> > values; //A vector of vectors. The inner vectors are the lines in data.txt
	int i, j, n, key, row = 0;    
	
	//Open the input/output files for reading and writing
	inFile.open("data.txt");
	outFile.open("merge.out");
	
	vector<int> nums;
    for (size_t i = 0; i < 12; i++)
        nums.push_back(rand() % 1000);
	
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
			mergeSort(values[row]);
			
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