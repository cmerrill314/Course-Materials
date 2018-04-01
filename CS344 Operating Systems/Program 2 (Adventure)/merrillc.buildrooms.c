/*------------------------------------------------------------------------------------
Christopher Merrill
CS344
Program 2: Adventure Game

This script is part 1 of a two part adventure game. It creates a graph that consists
of 7 rooms (chosen from a possible 10 at random), where each room has a name, a type
and connections to other rooms. Each room must have between 3 and 6 connections to 
other rooms.

Once the graph is created, the information for each room is copied into 7 external 
files. Each file contains the information for one distinct room. These files will be 
passed into part 2 of the program, which handles the game logic. 
------------------------------------------------------------------------------------*/
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

//The room struct will hold all of the information about a particular room
struct Room {
		const char *name;            //Room name 
		const char *type;            //Room type 
		const char *connections[6];  //An array of names that represent connections 
};

//This array will hold the final graph of 7 linked rooms
struct Room graph[7];

//Initialize 10 rooms to have type "MID_ROOM"
struct Room rooms[] = {
	{.name = "Hall", .type = "MID_ROOM"}, 
	{.name = "Closet", .type = "MID_ROOM"}, 
	{.name = "Library", .type = "MID_ROOM"}, 
	{.name = "Bathroom", .type = "MID_ROOM"}, 
	{.name = "Bedroom", .type = "MID_ROOM"}, 
	{.name = "Loft", .type = "MID_ROOM"}, 
	{.name = "Kitchen", .type = "MID_ROOM"}, 
	{.name = "Basement", .type = "MID_ROOM"}, 
	{.name = "Attic", .type = "MID_ROOM"}, 
	{.name = "Office", .type = "MID_ROOM"}
};

/*------------------------------------------------------------------------------------
ChooseRooms

This function determines which of the 10 rooms will be added to the graph array.
------------------------------------------------------------------------------------*/
void ChooseRooms() {
	int i;
	
	//Each iteration of the following for-loop will add one room to the graph array
	for(i=0; i<7; i++) {
		int roomCreated = 0; //Bool value that determines if a room was created
		
		//Keep looping through random rooms until one is found that wasn't taken
		while (roomCreated == 0) {
			//Randomly generate a number representing a room in the rooms array
			int r = rand() % 10;
			
			/*If this is the first Room added or if the room isn't already taken, 
			add the room to the graph */
			if (i == 0 || !IsNameTaken(rooms[r].name)) {
				graph[i] = rooms[r];
				roomCreated = 1;
			}
		}	
	}
}

/*------------------------------------------------------------------------------------
IsNameTaken

This function determines if a name has already been taken. It is used in the 
ChooseRooms function.

Input: A pointer to a name
Returns: A bool value (1 or 0) indicating if the passed name is taken or not
------------------------------------------------------------------------------------*/
int IsNameTaken(const char* name) {
	int nameTaken = 0; //Bool value
	int i;
	
	//Loop through the graph contents and determine if the passed name is already in use
	for (i=0; i<7; i++) 
		if (graph[i].name == name) 
			nameTaken = 1;
		
	return nameTaken;
}

/*------------------------------------------------------------------------------------
ChooseStartRoom

This function determines which of the 7 chosen rooms will be the START_ROOM.
------------------------------------------------------------------------------------*/
void ChooseStartRoom() {
	//Generate a random number from 0 to 6 and set that room as the starting room. 
	int r = rand() % 7;
	graph[r].type = "START_ROOM";
}

/*------------------------------------------------------------------------------------
ChooseEndRoom

This function determines which of the 7 chosen rooms will be the END_ROOM.
------------------------------------------------------------------------------------*/
void ChooseEndRoom() {
	int typeDeclared = 0;
	
	//Continue to loop through rooms until a valid END_ROOM is found
	while (typeDeclared == 0) {
		int r = rand() % 7;
		
		//Check if the randomly generated room is the START_ROOM. If not, set it as the
		//end room. 
		if (graph[r].type == "MID_ROOM") {
			graph[r].type = "END_ROOM";
			typeDeclared = 1;
		}
	}
}

/*------------------------------------------------------------------------------------
IsGraphFull

Checks to see if the graph is full. Used to determine when to stop adding connections.

Returns: True if all rooms have 3 to 6 outbound connections, false otherwise.
------------------------------------------------------------------------------------*/
int IsGraphFull() {
	int isGraphFull = 1; //Bool value initialized to true
	int i, j;

	
	//Loop through each room in graph and check their first 3 connections
	for (i=0; i<7; i++) 
		for (j=0; j<3; j++) 
			//If any of the first 3 connections are null, the graph isn't full
			if (graph[i].connections[j] == 0)
				isGraphFull = 0;
	
	return isGraphFull;
}

/*------------------------------------------------------------------------------------
CanAddConnectionFrom

Checks if a particular room can still add connections.

Input: The room to check
Returns: True if a connection can be added from Room x, false otherwise
------------------------------------------------------------------------------------*/
int CanAddConnectionFrom(struct Room x) {
	int n = 0; //The # of connections room x has
	int i;
	
	//Loop through each connection in x and increment x for each non-null value
	for (i=0;i<6;i++) 
		if (x.connections[i] != 0)
			n++;
	
	//If the number of connections is less than 6 return 1 (true)
	if (n < 6)
		return 1;
	else
		return 0;
}

/*------------------------------------------------------------------------------------
ConnectRoom

Adds room y as a connection to room x. 

Input: Two pointers to rooms
------------------------------------------------------------------------------------*/
void ConnectRoom(struct Room *x, struct Room *y) {
	int i;
	
	//Loop through room x's connections to find the first non-null value
	for (i=0; i<6; i++) {
		if (x->connections[i] == 0) {
			//Add room y as a connection for room x
			x->connections[i] = y->name;
			break;
		}
	}
}

/*------------------------------------------------------------------------------------
IsSameRoom

Determines if two rooms are the same room.

Input: Two rooms
Returns: True if Rooms x and y are the same Room, false otherwise
------------------------------------------------------------------------------------*/
int IsSameRoom(struct Room x, struct Room y) {
	//Compare the names of each room to determine if they are the same
	if (x.name == y.name)
		return 1;
	else
		return 0;
}

/*------------------------------------------------------------------------------------
IsConnected

Determines if two rooms are already connected.

Input: Two rooms
Returns: True if Rooms x and y are already connected, false otherwise
------------------------------------------------------------------------------------*/
int IsConnected(struct Room x, struct Room y) {
	int isConnected = 0; //Bool value
	int i;
	
	//Loop through each of room x's connections
	for (i=0;i<6;i++) 
		//If x's connection is equal to y's name, the rooms are already connected
		if (x.connections[i] == y.name)
			isConnected = 1;
	
	return isConnected;
}

/*------------------------------------------------------------------------------------
AddRandomConnections

Adds a random, valid outbound connection from a Room to another Room until the graph
is full.
------------------------------------------------------------------------------------*/
void AddRandomConnections() {
	//Continue to add connections until the graph is full
	while (IsGraphFull() == 0) {
		struct Room *A; //Pointer to a room
		struct Room *B; //Pointer to a room
		int isTrue = 1; 
		int r;
		
		//Set room A
		while(isTrue == 1) {
			//Choose a random room and set it to A
			r = rand() % 7;
			A = &graph[r];
			
			//If the randomly selected room has avaialbe connections, end the loop
			if (CanAddConnectionFrom(*A) == 1)
			break;
		}
		
		//Set room B
		do {
			//Choose a random room and set it to B
			r = rand() % 7;
			B = &graph[r];
		}
		//Continue to loop until room B is not the same as room A and has room for 
		//connections
		while(CanAddConnectionFrom(*B) == 0 || IsSameRoom(*A, *B) == 1);
		
		//Connect A and B if they aren't already connected
		if (IsConnected(*A, *B) == 0) {
			ConnectRoom(A, B);
			ConnectRoom(B, A);	
		}
	}
}

/*------------------------------------------------------------------------------------
CreateDirectory

Creates the directory that will hold the 7 room files and populates it.

The directory will have the naming convention: merrillc.rooms.<PID>
Each room file will be named: room<ROOM NUMBER>.txt
------------------------------------------------------------------------------------*/
void CreateDirectory() {
	FILE *tempFile;         //Points to a room file
	char fileName[64],      //Holds the file name of a room
	     directoryName[64], //Holds the name of the new directory
	     name[64],          //Holds the "ROOM NAME" line of a room file
	     type[64],          //Holds the "ROOM TYPE" line of a room file
	     connection[64];    //Holds a "CONNECTION" line of a room file
	int i, j;
	
	//Make a new directory
	sprintf(directoryName, "merrillc.rooms.%d", getpid());
	int result = mkdir(directoryName, 0755); 
	
	//Loop through each room in graph and add its data to a room file
	for(i=0;i<7;i++) {
		//Open a new room file in tempFile
		sprintf(fileName, "./%s/room%d.txt", directoryName, i);
		tempFile = fopen(fileName, "w+");
		
		//Put the "ROOM NAME" line into the room file
		sprintf(name, "ROOM NAME: %s\n", graph[i].name);
		fputs(name, tempFile);
		
		//Loop through each of the room's connections and add them to the room file
		for (j=0;j<6;j++) {
			if (graph[i].connections[j] != 0) {
				//If a connection exits, put it in the room file
				sprintf(connection, "CONNECTION %d: %s\n", (j+1), graph[i].connections[j]);
				fputs(connection, tempFile);
			}
		}
		
		//Put the "ROOM TYPE" line into the room file
		sprintf(type, "ROOM TYPE: %s\n", graph[i].type);
		fputs(type, tempFile);
		
		//Close the room file
		fclose(tempFile);
	}
}

int main() {	
	srand(time(NULL));      //Seed the random number generator
	ChooseRooms();          //Randomly choose 7 rooms to place in the graph
	ChooseStartRoom();      //Randomly choose the START_ROOM
	ChooseEndRoom();        //Randomly choose the END_ROOM 
	AddRandomConnections(); //Randomly add the connections between rooms
	CreateDirectory();      //Populate the directory of room files
	return 0;
}
