#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this

	//Create the sentinel
	list->sentinel = malloc(sizeof(struct Link));

	//Assert that the sentinel was created 
	assert(list->sentinel != NULL);

	//Update sentinel pointers
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;

	//Initialize size to 0
	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this

	//Create new link
	struct Link *newLink = malloc(sizeof(struct Link));
	
	//Update value
	newLink->value = value;

	//Update pointers
	newLink->next = NULL;
	newLink->prev = NULL;

	//Return the new link
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this

	//Assert that the provided link and list don't point to NULL
	assert(list != NULL);
	assert(link != NULL);

	//Create new link
	struct Link *newLink = createLink(value);

	//Store link's next value
	struct Link *temp = link->next;

	//Update pointers
	temp->prev = newLink;
	link->next = newLink;
	newLink->prev = link;
	newLink->next = temp;

	//Increment size
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this

	//Assert that link and list don't point to NULL
	assert(list != NULL);
	assert(link != NULL);

	//Store link's current pointers
	struct Link *prev = link->prev;
	struct Link *next = link->next;

	//Update pointers
	prev->next = next;
	next->prev = prev;

	//Decrement list size
	list->size--;

	//Remove the desired link
	free(link);
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this

	while (!circularListIsEmpty(list))
	{
		circularListRemoveFront(list);
	}
	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != NULL);

	//Use the addLinkBefore function to add a link to the front of the list
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != NULL);

	//Use the addLinkBefore function to add a link to the back of the list
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	//Assert that the list isn't NULL and isn't empty
	assert(list != NULL);
	assert(circularListIsEmpty(list) == 0);

	// FIXME: you must write this
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	//Assert that the list isn't NULL and isn't empty
	assert(list != NULL);
	assert(circularListIsEmpty(list) == 0);

	// FIXME: you must write this
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != NULL);

	//If the list isn't empty, remove the front value
	if (circularListIsEmpty(list) == 0)
		removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != NULL);

	//If the list isn't empty, remove the front value
	if (circularListIsEmpty(list) == 0)
		removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
	
	//Assert that the list isn't NULL
	assert(list != NULL);

	//Check if the list is empty
	if (list->size == 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != NULL);

	//If the list isn't empty, print the values
	if (circularListIsEmpty(list) == 0)
	{
		int i;

		//Create a temp link that will be printed
		struct Link *temp = list->sentinel->next;

		//Print each value, then increment temp
		for (i = 0; i < list->size; i++)
		{
			printf("%g\n", temp->value);
			temp = temp->next;
		}
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != NULL);

	//If the size is greater than 1, reverse the list
	if (list->size > 1)
	{
		int i;
		int count = list->size - 1;  //the number of times the for loop should run
		double value; //temporarily holds a link's value
		struct Link *temp; //temporarily holds a link

		//Initialize a placeholder that decides where a new link will be added
		struct Link *placeHolder = list->sentinel; 
		
		for (i = 0; i < count; i++)
		{
			//Store the back link and its value
			temp = list->sentinel->prev;
			value = temp->value;

			//Remove the back link
			circularListRemoveBack(list);

			//Add the back link after the placeholder value
			addLinkAfter(list, placeHolder, value);

			//Increment the placeholder location
			placeHolder = placeHolder->next;
		}
	}
}
