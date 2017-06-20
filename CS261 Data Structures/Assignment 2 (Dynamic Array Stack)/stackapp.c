/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null		
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */	

	int isBalanced = 0; //initialize isBalanced to false
	char letter = ' ';  //initialize letter to be blank

	//create a stack
	DynArr *stack;
	stack = newDynArr(2);

	//check if s is null
	if (s != 0)
	{
		//look through the string letter by letter until '\0' is encountered
		while (letter != '\0')
		{
			//if '(' is encountered, push ')' to the stack
			if (letter == '(')
				pushDynArr(stack, ')');
			//if '{' is encountered, push '}' to the stack
			else if (letter == '{')
				pushDynArr(stack, '}');
			//if '[' is encountered, push ']' to the stack
			else if (letter == '[')
				pushDynArr(stack, ']');
			//if ')' is encountered, check to see if it is the top item of the stack
			else if (letter == ')')
			{
				//if the closing bracket isn't a match or the stack is empty, 
				//add it to the stack and exit the loop
				if ((topDynArr(stack) != ')') || (isEmptyDynArr(stack) == 1))
				{
					pushDynArr(stack, ')');
					break;
				}
				//otherwise a match was found and the top of the stack can be popped
				else
					popDynArr(stack);
			}
			//if '}' is encountered, check to see if it is the top item of the stack
			else if (letter == '}')
			{
				//if the closing bracket isn't a match or the stack is empty, 
				//add it to the stack and exit the loop
				if (topDynArr(stack) != '}' || isEmptyDynArr(stack) == 1)
				{
					pushDynArr(stack, '}');
					break;
				}
				//otherwise a match was found and the top of the stack can be popped
				else
					popDynArr(stack);
			}
			//if ']' is encountered, check to see if it is the top item of the stack
			else if (letter == ']')
			{
				//if the closing bracket isn't a match or the stack is empty, 
				//add it to the stack and exit the loop
				if (topDynArr(stack) != ']' || isEmptyDynArr(stack) == 1)
				{
					pushDynArr(stack, ']');
					break;
				}
				//otherwise a match was found and the top of the stack can be popped
				else
					popDynArr(stack);
			}

			//set letter equal to the next character in s
			letter = nextChar(s);
		}
	}
	//if the string is null, print an error message 
	else
		printf("ERROR: No string provided\n");

		
	//if the stack is empty, set isBalanced to true
	if (isEmptyDynArr(stack) == 1)
		isBalanced = 1;

	//free data from the stack
	freeDynArr(stack);

	//free the stack itself
	deleteDynArr(stack);

	return isBalanced;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

