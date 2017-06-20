/*
 * CS 261 Data Structures
 * Assignment 6
 * Name: Christopher Merrill
 * Date: 3/9/2017
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }

    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }

    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));  
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;

    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
	HashLink *temp1 = NULL;
	HashLink *temp2 = NULL;

	//Loop through the map
	for (int i = 0; i < map->capacity; i++)
	{
		//If the table isn't NULL, delete its links
		if (map->table[i] != NULL)
		{
			temp1 = &map->table[i][0];
			temp2 = temp1->next;

			//Delete each link within the table
			while (temp1 != NULL)
			{
				temp2 = temp1->next;
				hashLinkDelete(temp1);
				temp1 = temp2;
			}
		}
	}

	//Free the table
	free(map->table);

	//Reset size and capaciity
	map->capacity = 0;
	map->size = 0;
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap)); 
    hashMapInit(map, capacity);

    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
	assert(map != NULL);

	//Find the index of the correct linked list bucket using HASH_FUNCTION(key)
	int index = HASH_FUNCTION(key);

	//Reduce to a valid index
	index %= map->capacity;

	//Adjust index to a positive value if necessary
	if (index < 0)
		index += map->capacity;

	HashLink *currentLink = map->table[index];

	//Sort through each link. 
	while (currentLink != NULL)
	{
		//If the key is found, return its value
		if (strcmp(currentLink->key, key) == 0)
			return &(currentLink->value);

		//Update currentLink
		currentLink = currentLink->next;
	}

	//If the key isn't found, return NULL
	return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
	// FIXME: implement
	assert(map != NULL);

	//Store the old table value and reinitialize map with the new capacity
	HashLink **oldTable = map->table;
	hashMapInit(map, capacity);

	HashLink *currentLink;
	HashLink *tempLink;

	//Transfer old links to new table
	for (int i = 0; i < ((map->capacity) / 2); i++)
	{
		if (oldTable[i] != NULL)
		{
			currentLink = oldTable[i];

			while (currentLink != NULL)
			{
				//Store the current link's next value in tempLink
				tempLink = currentLink->next;         

				//Add the current link to map
				hashMapPut(map, currentLink->key, currentLink->value);

				//Free the old link value
				hashLinkDelete(currentLink);

				//Update currentLink
				currentLink = tempLink;
			}
		}	
	}

	//Free the old table
	free(oldTable);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
	// FIXME: implement
	assert(map != NULL);

	//Find the index of the correct linked list bucket using HASH_FUNCTION(key)
	int index = HASH_FUNCTION(key);

	//Reduce to a valid index
	index %= map->capacity;

	//Adjust index to a positive value if necessary
	if (index < 0)
		index += map->capacity;

	//If the index is already in the table, update the value
	if (hashMapContainsKey(map, key) == 1)
	{
		HashLink *currentLink = map->table[index];
		
		//Loop through each link in the table to find the matching key
		while (currentLink != NULL)
		{
			//When the matching key is found, update its value and return
			if (strcmp(currentLink->key, key) == 0)
			{
				currentLink->value = value;
				return;
			}

			//update currentLink
			currentLink = currentLink->next;
		}
	}
	else
	{
		//Create a new link at the given index
		HashLink *newLink = hashLinkNew(key, value, map->table[index]);

		//Add the link to the table and increase the size
		map->table[index] = newLink;
		map->size++;

		//Resize if necessary
		if (hashMapTableLoad(map) > MAX_TABLE_LOAD)
			resizeTable(map, (2 * map->capacity));
	}
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
	// FIXME: implement
	assert(map != NULL);

	//Find the index of the correct linked list bucket using HASH_FUNCTION(key)
	int index = HASH_FUNCTION(key);

	//Reduce to a valid index
	index %= map->capacity;

	//Adjust index to a positive value if necessary
	if (index < 0)
		index += map->capacity;

	HashLink *link = map->table[index];

	//If the initial link matches the desired key, remove it with hashLinkDelete(link)
	if (strcmp(link->key, key) == 0)
	{
		//Store the next link in temp
		HashLink *temp = link->next;

		//Delete link
		hashLinkDelete(link);

		//Set link's index equal to the next value (temp)
		map->table[index] = temp;

		//Update the map size
		map->size--;

		return;
	}

	//Loop through table. If the key is found, remove that link with hashLinkDelete(link)
	while (link->next != NULL)
	{
		if (strcmp(link->next->key, key) == 0)
		{
			//Store the next link in temp
			HashLink *temp = link->next->next;

			//Delete link
			hashLinkDelete(link->next);

			//Replace link with the next value (temp)
			link->next = temp;

			//Update the map size
			map->size--;
			return;
		}

		//Increment to the next link
		link = link->next;
	}
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
	assert(map != NULL);

	//Find the index of the correct linked list bucket using HASH_FUNCTION(key)
	int index = HASH_FUNCTION(key);

	//Reduce to a valid index
	index %= map->capacity;

	//Adjust index to a positive value if necessary
	if (index < 0)
		index += map->capacity;

	HashLink *link = map->table[index];

	//Loop through the table 
	while (link != NULL)
	{
		//Return 1 if the key is found
		if (strcmp(link->key, key) == 0)
			return 1;

		//Increment to the next link
		link = link->next;
	}

	return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
	assert(map != NULL);

	return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
	assert(map != NULL);

	return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
	assert(map != NULL);
	int emptyBuckets = 0;

	//Loop through the map
	for (int i = 0; i < map->capacity; i++)
	{
		//If an empty bucket is found, increment emptyBuckets
		if (map->table[i] == NULL)
			emptyBuckets++;
	}

	return emptyBuckets;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
	assert(map != NULL);

	//Calculate the table's load factor using the  float values of map size and map capacity.
	float ratio = (float)map->size / (float)map->capacity;

	return ratio;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}