/* CS261- Assignment 1 - Q.5*/
/* Name: Christopher Merrill
* Date: 1/9/2017
* Solution description: Converts a user-entered word into sticky caps, using the
* instructor provided functions toUpperCase and toLowerCase.
*/
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
	int i = 0;

	//cycle through each letter of the word and convert case as necessary
	while (word[i] != '\0'){
		//if i is even, the character should be uppercase
		if (i % 2 == 0) {
			//make sure the letter isnt already uppercase before converting
			if (word[i] >= 'a' && word[i] <= 'z') {
				word[i] = toUpperCase(word[i]);
			}
		}
		//otherwise the character should be lowercase
		else {
			//make sure the letter isnt already lowercase before converting
			if (word[i] >= 'A' && word[i] <= 'Z') {
				word[i] = toLowerCase(word[i]);
			}
		}	
		i++;
	}
}

int main(){
    /*Read word from the keyboard using scanf*/
	char string[100]; //allows for words up to 100 characters
	printf("Enter a word to convert to sticky caps:\n");
	scanf("%s", string);

    /*Call sticky*/
	sticky(string);

    /*Print the new word*/
	printf("Result: %s\n", string);

    return 0;
}
