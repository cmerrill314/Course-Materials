/* CS261- Assignment 1 - Q.1*/
/* Name: Christopher Merrill
* Date: 1/9/2017
* Solution description: Generates random ID numbers and grade values 
* for 10 students and prints the results. 
*/
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/	
	struct student *st = malloc(10 * sizeof *st);

	/*return the pointer*/
	return st;
}

void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	int i; 
	int j;
	int idValue;
	int scoreValue;
	int isUnique = 0;
	int matchFound = 0;

	for (i = 0; i < 10; i++){
		//generate new ID/score
		idValue = rand() % 10 + 1; //generate random ID from 1 to 10
		scoreValue = rand() % 101; //generate random score between 0 to 100

		//check if the generated ID is unique
		if (i != 0){
			while (isUnique == 0){
				//loop through previous values to see if the generated ID matches any of the previous id's
				for (j = 0; j < i; j++){
					if (idValue == students[j].id){
						matchFound = 1; //indicate a match has been found
					}
				}

				//if a match was found, generate a new ID and try again
				if (matchFound == 1){
					idValue = rand() % 10 + 1; //generate new random ID from 1 to 10
				}
				//otherwise exit the while loop
				else{
					isUnique = 1;
				}

				//reset matchFound
				matchFound = 0;
			}
		}
		
		//set values
		students[i].id = idValue;
		students[i].score = scoreValue;

		//reset isUnique
		isUnique = 0;
	 }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	int i;

	for (i = 0; i < 10; i++){
		printf("ID: %d Score: %d\n", students[i].id, students[i].score);
	}

	printf("\n");
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int i;
	int min = 100;
	int max = 0;
	int sum = 0;
	double average;

	//compute minimum, maximum and sum
	for (i = 0; i < 10; i++){
		//update minimum
		if (students[i].score < min){
			min = students[i].score;
		}

		//update maximum
		if (students[i].score > max){
			max = students[i].score;
		}

		//update sum
		sum = sum + students[i].score;
	}
     
	//compute average
	average = sum / 10;

	//print results
	printf("Minimum Score: %d\nMaximum Score: %d\nAverage Score: %f\n\n", min, max, average);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	if (stud != NULL) {
		free(stud);
	}
}

int main(){
    struct student *stud = NULL;

    /*call allocate*/
	stud = allocate();

    /*call generate*/
	generate(stud);

    /*call output*/
	output(stud);
    
    /*call summary*/
	summary(stud);
    
    /*call deallocate*/
	deallocate(stud);

    return 0;
}
