/* CS261- Assignment 1 - Q.2*/
/* Name: Christopher Merrill
* Date: 1/9/2017
* Solution description: Uses a combination of pointers and non-pointers as
* function parameters to demonstrate the difference. 
*/
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = 2 * *a;
    /*Set b to half its original value*/
	*b = *b / 2;
    /*Assign a+b to c*/
	c = *a + *b;
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;
    /*Print the values of x, y and z*/
	printf("x-value: %d\n", x);
	printf("y-value: %d\n", y);
	printf("z-value: %d\n", z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
	int value = foo(&x, &y, z);
    /*Print the value returned by foo*/
	printf("value returned by foo: %d\n", value);
    /*Print the values of x, y and z again*/
	printf("x-value: %d\n", x);
	printf("y-value: %d\n", y);
	printf("z-value: %d\n", z);

    return 0;
}
    
/*Is the return value different than the value of z?  Why?*/

/*ANSWER: Yes because the value of z is not altered while running foo. A
copy of z is used within foo and its a copy that is returned. Therefore
the original value of z remains unchanged in the final round of printing.
However x and y ARE altered within foo because foo has access to their
memory locations. */
