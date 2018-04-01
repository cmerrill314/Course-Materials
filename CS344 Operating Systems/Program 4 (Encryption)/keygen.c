/*************************************************
Christopher Merrill                              * 
CS344                                            *
Program 4                                        *
                                                 *
This file handles the encryption key generation. *
*************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]) {
	int keyLength, ranVal, ranChar, i;

	//Seed the random number generator
	srand(time(NULL));
	
	//Check arguments
	if (argc < 2) {printf("ERROR: Key length not specified"); exit(0);}

	//Set the key length using the key length argument
	keyLength = atoi(argv[1]);

	//Create the encryption key
	for (i = 0; i < keyLength; i++) {
		//Generate a random integer
		ranVal = rand() % 27;
		
		//Convert the random integer into a character or space
		if(ranVal < 26) {ranChar = 65 + ranVal; printf("%c", ranChar);}
		else printf(" "); //Space case
	}

	//New line
	printf("\n");

	return 0;
}