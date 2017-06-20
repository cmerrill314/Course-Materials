/*
 * CS 261 Assignment 5
 * Name: Christopher Merrill
 * Date: 3/5/2017
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name)
{
    // FIXME: implement
	
	//Create a new task
	struct Task  *task = malloc(sizeof(struct Task));

	//Update task values
	strcpy(task->name, name);
	task->priority = priority;

	return task;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
    // FIXME: implement

	//Type cast to the corresponding pointer type
	struct Task *tempLeft = left;
	struct Task *tempRight = right;

	//Perform the comparisons and return the corresponding result
	if (tempLeft->priority < tempRight->priority)
		return -1;
	else if (tempLeft->priority > tempRight->priority)
		return 1;
	else
		return 0;
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("(%d, %s)", task->priority, task->name);
}
