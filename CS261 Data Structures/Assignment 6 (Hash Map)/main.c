#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---
    // Be sure to free the word after you are done with it here.
	char *word;       
	FILE *inputFile;

	//Open the desired file and store it in inputFile
	inputFile = fopen(fileName, "r");

	//Loop through each word in the file
	while ((word = nextWord(inputFile)))
	{
		//If the word is already in the hashMap, increment its value
		if (hashMapContainsKey(map, word) == 1)
		{
			//Use hashMapGet to retrieve a pointer to the desired value
			int *value = hashMapGet(map, word);

			//Increment the word's value
			(*value)++;
		}
		//If the word isn't already in the hashMap, add it with an occurence of 1
		else
			hashMapPut(map, word, 1);

		//Free word
		free(word);
	}

	printf("\n");

	//Display the count of each word in the input file
	for (int i = 0; i < map->capacity; i++)
	{
		HashLink *currentLink = &map->table[i][0];

		//Loop through each link in map
		while (currentLink != NULL)
		{
			//Print the word (key) and the number of occurences (value)
			printf("%s: %d\n", currentLink->key, currentLink->value);

			//Increment to the next link
			currentLink = currentLink->next;
		}
	}

	//Close the file
	fclose(inputFile);

	printf("\n");

    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}