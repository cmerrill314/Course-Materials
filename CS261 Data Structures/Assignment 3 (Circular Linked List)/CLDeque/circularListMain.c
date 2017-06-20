#include "circularList.h"
#include <stdio.h>

int main()
{	
	struct CircularList* deque = circularListCreate(); 
	circularListAddBack(deque, (TYPE)1);
	circularListAddBack(deque, (TYPE)2);
	circularListAddBack(deque, (TYPE)3);
	circularListAddFront(deque, (TYPE)4);
	circularListAddFront(deque, (TYPE)5);
	circularListAddFront(deque, (TYPE)6);

	printf("PRINT #1: Should be 6 5 4 1 2 3\n\n");
	circularListPrint(deque);
	printf("FRONT VALUE: %g\n", circularListFront(deque));
	printf("BACK VALUE: %g\n", circularListBack(deque));
	
	printf("PRINT #2: Should be 5 4 1 2\n\n");
	circularListRemoveFront(deque);
	circularListRemoveBack(deque);
	circularListPrint(deque);
	
	printf("PRINT #2: Should be 2 1 4 5\n\n");
	circularListReverse(deque);
	circularListPrint(deque);
	
	circularListDestroy(deque);
	
	return 0;
}
