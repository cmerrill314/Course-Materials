/* CS261- Assignment 1 - Q.4*/
/* Name: Christopher Merrill
* Date: 1/9/2017
* Solution description: Generates an array of 10 students, sorts the students
* based on scores, and displays the results.
*/
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/    

	int i, j;
	struct student temp;

	//using bubble sort method
	for (i = 0; i < (n - 1); i++) {
		for (j = 0; j < (n - i - 1); j++) {
			if (students[j].score > students[j + 1].score)
			{
				temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value.*/
	int n = 10;
    
    /*Allocate memory for n students using malloc.*/
	struct student *stud = malloc(n * sizeof *stud);
    
    /*Generate random and unique IDs and random scores for the n students, using rand().*/

	//USING THE METHOD DEVELOPED IN THE GENERATE FUNTION OF Q1:
	int i;
	int j;
	int idValue;
	int scoreValue;
	int isUnique = 0;
	int matchFound = 0;

	for (i = 0; i < n; i++) {
		//generate new ID/score
		idValue = rand() % 10 + 1; //generate random ID from 1 to 10
		scoreValue = rand() % 101; //generate random score between 0 to 100

		//check if the generated ID is unique
		if (i != 0) {
			while (isUnique == 0) {
				//loop through previous values to see if the generated ID matches any of the previous id's
				for (j = 0; j < i; j++) {
					if (idValue == stud[j].id) {
						matchFound = 1; //indicate a match has been found
					}
				}

				//if a match was found, generate a new ID and try again
				if (matchFound == 1) {
					idValue = rand() % 10 + 1; //generate new random ID from 1 to 10
				}
				//otherwise exit the while loop
				else {
					isUnique = 1;
				}

				//reset matchFound
				matchFound = 0;
			}
		}

		//set values
		stud[i].id = idValue;
		stud[i].score = scoreValue;

		//reset isUnique
		isUnique = 0;
	}

    /*Print the contents of the array of n students.*/
	printf("UNSORTED VALUES:\n");
	
	for (i = 0; i < n; i++) {
		printf("ID: %d Score: %d\n", stud[i].id, stud[i].score);
	}

	printf("\n");

    /*Pass this array along with n to the sort() function*/
	sort(stud, n);

    
    /*Print the contents of the array of n students.*/
	printf("SORTED VALUES:\n");

		for (i = 0; i < n; i++) {
			printf("ID: %d Score: %d\n", stud[i].id, stud[i].score);
		}

	printf("\n");

	//free allocated memory
	if (stud != NULL){
		free(stud);
	}

    return 0;
}
