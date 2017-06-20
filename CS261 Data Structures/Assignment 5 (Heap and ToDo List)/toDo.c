/*
 * CS 261 Assignment 5
 * Name: Christopher Merrill
 * Date: 3/5/2017
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
	if (command == 'l')
	{
		char fileName[100];
		FILE *file;

		//Ask the user to enter a filename
		printf("\nEnter the name of the file you wish to load: ");
		scanf("%s", fileName);
		getchar();

		//Call fopen() to open the file
		file = fopen(fileName, "r");

		//Call listLoad() to load the desired file
		listLoad(list, file);

		//Call fclose() to close the file
		fclose(file);

		printf("\n");
	}
	else if (command == 's')
	{
		char fileName[100];
		FILE *file;

		//Ask the user to enter a filename
		printf("\nEnter the name of the file you wish to save to (press enter twice when finished): ");
		scanf("%[^\n]%*c", fileName);
		//while (getchar() != '\n');
		getchar();

		//Call fopen() to open the file
		file = fopen(fileName, "w");

		//Call listSave() to save to the desired file
		listSave(list, file);

		//Call fclose() to close the file
		fclose(file);

		printf("\n");
	}
	else if (command == 'a')
	{
		char taskName[100];
		int taskPriority;
		struct Task *task;

		//Ask the user to enter a task and give it a priority value
		printf("\nEnter task (press enter twice when finished): ");
		scanf("%[^\n]%*c", taskName);
		getchar();
		printf("Enter priority: ");
		scanf("%d", &taskPriority);
		getchar();

		//Create the task using taskNew() and add it to list
		task = taskNew(taskPriority, taskName);
		dyHeapAdd(list, task, taskCompare);

		printf("\n");
	}
	else if (command == 'g')
	{
		//Make sure there is a value to get
		if (dySize(list) > 0)
		{
			//Call dyHeapGetMin() to retrieve the first value of list
			struct Task *task = dyHeapGetMin(list);
			printf("\nThe first task of your To-Do list is to: %s\n", task->name);
		}
		else
			printf("\nNo items to get...\n");
		
	}
	else if (command == 'r')
	{
		//Make sure there is a value to remove
		if (dySize(list) > 0)
		{
			//Call dyHeapRemoveMin() to remove the first value of list
			struct Task *task = dyHeapGetMin(list);
			dyHeapRemoveMin(list, taskCompare);
			printf("\nTask Removed: %s\n", task->name);

			free(task);
		}
		else
			printf("\nNo items to remove...\n");
	}
	else if (command == 'p')
	{
		//Call listPrint() to print the list
		listPrint(list);
		printf("\n");
	}	
	else if (command != 'e')
	{
		//Inform the user if they didn't enter a menu option
		printf("\nInvalid Entry: Please enter a value from the menu\n");
	}	
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
 
	/* free dynamically allocated List pointers in array to avoid memory leaks */
	while (dySize(list) > 0)
	{
		struct Task *temp = dyHeapGetMin(list);
		dyHeapRemoveMin(list, taskCompare);
		free(temp);
	}

    dyDelete(list);
    return 0;
}