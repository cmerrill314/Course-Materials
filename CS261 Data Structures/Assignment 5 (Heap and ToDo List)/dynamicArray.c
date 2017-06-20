/*
 * CS 261 Assignment 5
 * Name: Christopher Merrill
 * Date: 3/5/2017
 */

#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TESTING

#ifndef TESTING
static void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare);
static void buildHeap(DynamicArray* heap, compareFunction compare);
#endif

struct DynamicArray
{
    TYPE* data;
    int size;
    int capacity;
};

// --- Dynamic array ---

static void setCapacity(DynamicArray* array, int capacity)
{
    TYPE* data = malloc(sizeof(TYPE) * capacity);
    for (int i = 0; i < array->size; i++)
    {
        data[i] = array->data[i];
    }
    free(array->data);
    array->data = data;
    array->capacity = capacity;
}

static void init(DynamicArray* array, int capacity)
{
    assert(capacity > 0);
    array->data = NULL;
    array->size = 0;
    setCapacity(array, capacity);
}

DynamicArray* dyNew(int capacity)
{
    DynamicArray* array = malloc(sizeof(DynamicArray));
    init(array, capacity);
    return array;
}

void dyDelete(DynamicArray* array)
{
    free(array->data);
    free(array);
}

void dyAdd(DynamicArray* array, TYPE value)
{
    if (array->size >= array->capacity)
    {
        setCapacity(array, 2 * array->capacity);
    }
    array->data[array->size] = value;
    array->size++;
}

void dyAddAt(DynamicArray* array, TYPE value, int position)
{
    assert(position <= array->size);
    dyAdd(array, value);
    for (int i = array->size - 1; i > position; i--)
    {
        dySwap(array, i, i - 1);
    }
}

void dyPut(DynamicArray* array, TYPE value, int position)
{
    assert(position < array->size);
    array->data[position] = value;
}

void dyRemoveAt(DynamicArray* array, int position)
{
    assert(position < array->size);
    for (int i = position; i < array->size - 1; i++)
    {
        array->data[position] = array->data[position + 1];
    }
    array->size--;
}

TYPE dyGet(DynamicArray* array, int position)
{
    assert(position < array->size);
    return array->data[position];
}

int dySize(DynamicArray* array)
{
    return array->size;
}

void dySwap(DynamicArray* array, int position1, int position2)
{
    assert(position1 < array->size);
    assert(position2 < array->size);
    TYPE temp = array->data[position1];
    array->data[position1] = array->data[position2];
    array->data[position2] = temp;
}

// --- Stack ---

void dyStackPush(DynamicArray* stack, TYPE value)
{
    dyAdd(stack, value);
}

void dyStackPop(DynamicArray* stack)
{
    dyRemoveAt(stack, stack->size - 1);
}

TYPE dyStackTop(DynamicArray* stack)
{
    return dyGet(stack, stack->size - 1);
}

int dyStackIsEmpty(DynamicArray* stack)
{
    return stack->size == 0;
}

// --- Bag ---

static int findFirst(DynamicArray* array, TYPE value, compareFunction compare)
{
    for (int i = 0; i < array->size; i++)
    {
        if (compare(value, array->data[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

void dyBagAdd(DynamicArray* bag, TYPE value)
{
    dyAdd(bag, value);
}

void dyBagRemove(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = findFirst(bag, value, compare);
    if (position != -1)
    {
        dyRemoveAt(bag, position);
    }
}

int dyBagContains(DynamicArray* bag, TYPE value, compareFunction compare)
{
    return findFirst(bag, value, compare) != -1;
}

// --- Ordered bag ---

static int binarySearch(DynamicArray* array, TYPE value, compareFunction compare)
{
    int low = 0;
    int high = array->size - 1;
    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (compare(value, array->data[middle]) < 0)
        {
            high = middle - 1;
        }
        else if (compare(value, array->data[middle]) > 0)
        {
            low = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    return low;
}

void dyOrderedAdd(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = binarySearch(bag, value, compare);
    dyAddAt(bag,value, position);
}

void dyOrderedRemove(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = binarySearch(bag, value, compare);
    if (compare(value, bag->data[position]) == 0)
    {
        dyRemoveAt(bag, position);
    }
}

int dyOrderedContains(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = binarySearch(bag, value, compare);
    return compare(value, dyGet(bag, position)) == 0;
}

// --- Heap ---

/**
 * Adjusts heap to maintain the heap property.
 * @param heap
 * @param last  index to adjust up to.
 * @param position  index where adjustment starts.
 * @param compare  pointer to compare function.
 */
void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare)
{
    // FIXME: implement
	assert(heap != 0);

	int leftChild = 2 * position + 1;
	int rightChild = 2 * position + 2;

	//CASE: TWO CHILDREN
	if (rightChild < last)
	{
		//get the index of the smallest of the two children
		int smallest;

		//assure that rightChild and leftChild are within the bounds of heap
		if (leftChild < heap->size && rightChild < heap->size)
		{
			//set smallest equal to the smaller of the two children
			if (compare(heap->data[leftChild], heap->data[rightChild]) == -1)
				smallest = leftChild;
			else
				smallest = rightChild;
		}

		//if the value at smallest is less than the value at position, swap them
		if (compare(heap->data[smallest], heap->data[position]) == -1)
		{
			dySwap(heap, smallest, position);

			//perform another heap adjustment
			adjustHeap(heap, last, smallest, compare);
		}
	}
	//CASE: ONE CHILD
	else if (leftChild < last)
	{
		//assure that leftChild and position are within the bounds of heap
		if (leftChild < heap->size && position < heap->size)
		{
			//if the value at leftChild is less than the value at position, swap them
			if (compare(heap->data[leftChild], heap->data[position]) == -1)
			{
				dySwap(heap, leftChild, position);

				//perform another heap adjustment
				adjustHeap(heap, last, leftChild, compare);
			}
		}
	}
	//CASE: NO CHILDREN
	else
		return;
}

/**
 * Builds a valid heap from an arbitrary array.
 * @param heap  array with elements in any order.
 * @param compare  pointer to compare function.
 */
void buildHeap(DynamicArray* heap, compareFunction compare)
{
    // FIXME: implement
	assert(heap != 0);
	assert(heap->size != 0);

	int i;

	//Start at the index of the first value that isn't a leaf
	for (i = (heap->size) / 2 - 1; i >= 0; i--)
	{
		//Adjust each subtree
		adjustHeap(heap, heap->size, i, compare);
	}
		
}

/**
 * Adds an element to the heap.
 * @param heap
 * @param value  value to be added to heap.
 * @param compare  pointer to compare function.
 */
void dyHeapAdd(DynamicArray* heap, TYPE value, compareFunction compare)
{
    // FIXME: implement
	assert(heap != 0);

	int i;
	int parent;

	//Expand the capacity of the heap if necessary
	if (heap->size == heap->capacity)
		setCapacity(heap, 2 * heap->capacity);

	//Add element to the heap
	heap->data[heap->size] = value;
	heap->size++;

	//Update the index i
	i = heap->size - 1;

	//Loop through the heap, swapping values as necessary
	while (i != 0)
	{
		//Update the parent
		parent = (i - 1) / 2;

		//Swap values if the value at i is less than the parent value
		if (compare(heap->data[i], heap->data[parent]) == -1)
		{
			dySwap(heap, parent, i);
			i = parent;
		}
		else
			return;
	}
}

/**
 * Removes the first element, which has the min priority, form the heap.
 * @param heap
 * @param compare  pointer to the compare function.
 */
void dyHeapRemoveMin(DynamicArray* heap, compareFunction compare)
{
    // FIXME: implement
	assert(heap != 0);
	assert(heap->size != 0);

	//Overite the min value with the last value in the heap 
	heap->data[0] = heap->data[heap->size - 1];
	heap->size--;

	//Adjust the heap
	adjustHeap(heap, heap->size, 0, compare);
}

/**
 * Returns the first element, which has the min priority, from the heap.
 * @param heap
 * @return  Element at the top of the heap.
 */
TYPE dyHeapGetMin(DynamicArray* heap)
{
    // FIXME: implement
	assert(heap != 0);
	assert(heap->size != 0);

	//Return the value position 0
    return heap->data[0];
}

/**
 * Sorts arbitrary array in-place.
 * @param heap  array with elements in arbitrary order.
 * @param compare  pointer to the compare function.
 */
void dyHeapSort(DynamicArray* heap, compareFunction compare)
{
    // FIXME: implement
	assert(heap != 0);
	assert(heap->size != 0);

	int i;

	//Transform the array into a heap 
	buildHeap(heap, compare);

	//Loop through the array
	for (i = heap->size - 1; i >= 0; i--)
	{
		//Swap i to the min position
		dySwap(heap, 0, i);

		//Adjust the heap
		adjustHeap(heap, i, 0, compare);
	}
}

// --- Iterator ---

DynamicArrayIterator* dyIteratorNew(DynamicArray* array)
{
    DynamicArrayIterator* iterator = malloc(sizeof(DynamicArrayIterator));
    iterator->array = array;
    iterator->current = 0;
    return iterator;
}

void dyIteratorDelete(DynamicArrayIterator* iterator)
{
    free(iterator);
}

int dyIteratorHasNext(DynamicArrayIterator* iterator)
{
    return iterator->current < iterator->array->size;
}

TYPE dyIteratorNext(DynamicArrayIterator* iterator)
{
    TYPE value = dyGet(iterator->array, iterator->current);
    iterator->current++;
    return value;
}

void dyIteratorRemove(DynamicArrayIterator* iterator)
{
    iterator->current--;
    dyRemoveAt(iterator->array, iterator->current);
}

// --- Utility ---

void dyPrint(DynamicArray* array, printFunction print)
{
    printf("\nsize: %d\ncapacity: %d\n[\n", array->size, array->capacity);
    for (int i = 0; i < array->size; i++)
    {
        printf("%d : ", i);
        print(array->data[i]);
        printf("\n");
    }
    printf("]\n");
}

void dyCopy(DynamicArray* source, DynamicArray* destination)
{
    free(destination->data);
    init(destination, source->capacity);
    for (int i = 0; i < source->size; i++)
    {
        destination->data[i] = source->data[i];
    }
    destination->size = source->size;
}