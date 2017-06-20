/* CS261- Assignment 1 - Q.3*/
/* Name: Christopher Merrill
* Date: 1/9/2017
* Solution description: Generates an array of 20 random integers, sorts the array
* and displays the results. 
*/
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n){
     /*Sort the given array number , of length n*/
	int i, j, temp;

	//using bubble sort method
	for (i = 0; i < (n - 1); i++){
		for (j = 0; j < (n - i - 1); j++) {
			if (number[j] > number[j + 1])
			{
				temp = number[j];
				number[j] = number[j + 1];
				number[j + 1] = temp;
			}
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
	int *aryOfInts = malloc(n * sizeof *aryOfInts);

	/*Fill this array with random numbers, using rand().*/
	int i;

	for (i = 0; i < n; i++){
		aryOfInts[i] = rand() % 100;
	}
    
    /*Print the contents of the array.*/
	printf("Unsorted Array Contents: ");
	
	for (i = 0; i < n; i++){
		printf("%d ", aryOfInts[i]);
	}

	printf("\n");

    /*Pass this array along with n to the sort() function of part a.*/
	sort(aryOfInts, n);
    
    /*Print the contents of the array.*/    
	printf("Sorted Array Contents: ");

	for (i = 0; i < n; i++) {
		printf("%d ", aryOfInts[i]);
	}

	printf("\n");

	//free allocated memory
	if (aryOfInts != NULL) {
		free(aryOfInts);
	}

    return 0;
}
