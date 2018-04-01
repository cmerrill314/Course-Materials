#include <vector>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctgmath>
#include <climits>
using namespace std;

int main()
{
	vector<int> coins; //Holds the array of coins
	int n = 6400;       //The number of coins 
	int v = 640000;       //The value that we are making change for
	clock_t start;     //Start time
	double runtime;    //Run time
	int i, j, k, subResult, luck, val, prevN, count = 0; 
	
	//Seed the random number generator
	srand(time(NULL));
	
	//Perform 5 rounds of insertion sort, doubling n each time
	//while (count < 8) {
		//First value should be 10
		val = 1;
		prevN = 1;
		
		//Add n coins to the vector
		for (i = 0; i < n; i++) {
			coins.push_back(val); 
			val++;
			
			//Generate a random value from 1 to 10 to add to the current coin value
			luck = rand() % 11;
			val = prevN + luck;
		}
		
		//Start the clock
		start = clock();
		
		int results[v + 1];      //Stores the min number of coins required for each value up to v+1
		static int coinsUsed[640001][6400]; //Stores the number of each denomination of coin used to reach the result
	 
		//Base case
		results[0] = 0;
	 
		//Initialize all results values to be infinite
		for (i = 1; i <= v; i++) {
			results[i] = INT_MAX;
		}
		
		//Initialize all coinsUsed values to be 0
		for (i = 0; i <= val; i++) {
			for (j = 0; j < n; j++) {
				coinsUsed[i][j] = 0;
			}
		}
	 
		//Determine the min coins required for all values from 1 to v
		for (i = 1; i <= v; i++) {
			//Loop through all coins smaller than i
			for (j = 0; j < n; j++) {
				//Check if the coin value is less than v
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
		
		//Add minimum number of coins to file
		cout << "MIN NUMBER OF COINS: " << results[v] << endl;
		
		//Calculate the runtime
		runtime = (clock() - start) / (double) CLOCKS_PER_SEC;
		cout << "MAKE CHANGE RUNTIME FOR " << n << " COINS AND V-VALUE " << v << ": " << runtime << endl;
		
		//Clear coins contents
		coins.clear();
		
		//Increment count and double n-value
		//count++;
		n *= 2;
		v*= 2;
	//}
	
    return 0;
}