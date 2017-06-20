#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
* Allocates the list's sentinel and sets the size to 0.
* The sentinels' next and prev should point to eachother or NULL
* as appropriate.
*/
static void init(struct LinkedList* list) {
	// FIXME: you must write this

	//Create the front sentinel
	list->frontSentinel = malloc(sizeof(struct Link));

	//Assert that the frontSentinel was created and doesn't point to null
	assert(list->frontSentinel != 0);

	//Create the back sentinel
	list->backSentinel = malloc(sizeof(struct Link));

	//Assert that backSentinel was created and doesn't point to null
	assert(list->backSentinel != 0);

	//Update sentinels for an initially empty list
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->frontSentinel->prev = 0;
	list->backSentinel->next = 0;

	//Initialize size to zero
	list->size = 0;
}

/**
* Adds a new link with the given value before the given link and
* increments the list's size.
*/
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this

	//Assert that the provided link and list don't point to NULL
	assert(list != 0);
	assert(link != 0);

	//Create the new link
	struct Link *newLink = malloc(sizeof(struct LinkedList));

	//Store the value of the previous link
	struct Link *temp = link->prev;

	//Update the previous link's next pointer
	temp->next = newLink;

	//Update link's previous pointer to point to the new link
	link->prev = newLink;

	//Update the new links pointers
	newLink->value = value;
	newLink->next = link;
	newLink->prev = temp;

	//Increment list size
	list->size++;
}

/**
* Removes the given link from the list and
* decrements the list's size.
*/
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this

	//Assert that link and list don't point to NULL
	assert(list != 0);
	assert(link != 0);

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
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
* Deallocates every link in the list including the sentinels,
* and frees the list itself.
*/
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
* Adds a new link with the given value to the front of the deque.
*/
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != 0);

	//Use the addLinkBefore function to add a link to the front of the deque
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
* Adds a new link with the given value to the back of the deque.
*/
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != 0);

	//Use the addLinkBefore function to add a link to the back of the deque
	addLinkBefore(list, list->backSentinel, value);
}

/**
* Returns the value of the link at the front of the deque.
*/
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL and isn't empty
	assert(list != 0);
	assert(linkedListIsEmpty(list) == 0);

	//Return the value pointed to by the front sentinel of the deque
	return list->frontSentinel->next->value;
}

/**
* Returns the value of the link at the back of the deque.
*/
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL and isn't empty
	assert(list != 0);
	assert(linkedListIsEmpty(list) == 0);

	//Return the value pointed to by the back sentinel of the deque
	return list->backSentinel->prev->value;
}

/**
* Removes the link at the front of the deque.
*/
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != 0);

	//If the deque isn't empty, remove the front value
	if (linkedListIsEmpty(list) == 0)
		removeLink(list, list->frontSentinel->next);
}

/**
* Removes the link at the back of the deque.
*/
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != 0);

	//If the deque isn't empty, remove the back value
	if (linkedListIsEmpty(list) == 0)
		removeLink(list, list->backSentinel->prev);
}

/**
* Returns 1 if the deque is empty and 0 otherwise.
*/
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != 0);

	//Check if the list is empty
	if (list->size == 0)
		return 1;
	else
		return 0;
}

/**
* Prints the values of the links in the deque from front to back.
*/
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != 0);

	//If the list isn't empty, print the values
	if (linkedListIsEmpty(list) == 0)
	{
		int i;

		//Create a temp link that will be printed
		struct Link *temp = list->frontSentinel->next;

		//Print each value, then increment temp
		for (i = 0; i < list->size; i++)
		{
			printf("%d\n", temp->value);
			temp = temp->next;
		}
	}
}

/**
* Adds a link with the given value to the bag.
*/
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != 0);

	//Use the addLinkBefore function to add a link to the bag
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
* Returns 1 if a link with the value is in the bag and 0 otherwise.
*/
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != 0);

	//If the list isn't empty, check for the value
	if (linkedListIsEmpty(list) == 0)
	{
		int i;

		//Create a temp link that will be used to compare values
		struct Link *temp = list->frontSentinel->next;

		//Loop through the list to search for the desired value
		for (i = 0; i < list->size; i++)
		{
			//If the desired value is found, return 1
			if (temp->value == value)
				return 1;

			//Move to the next item in the bag
			temp = temp->next;
		}
	}

	return 0;
}

/**
* Removes the first occurrence of a link with the given value.
*/
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//Assert that the list isn't NULL
	assert(list != 0);

	//If the list isn't empty, check for the value
	if (linkedListIsEmpty(list) == 0)
	{
		int i;

		//Create a temp link that will be printed
		struct Link *temp = list->frontSentinel->next;

		//Loop through the list to search for the desired value
		for (i = 0; i < list->size; i++)
		{
			//If the desired value is found, remove it
			if (temp->value == value)
			{
				removeLink(list, temp);
				break;
			}
				
			//Move to the next item in the bag
			temp = temp->next;
		}
	}
}