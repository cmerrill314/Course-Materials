/*------------------------------------------------------------------------------------
Christopher Merrill
CS344
Program 2: Adventure Game

This script is part 2 of a two part adventure game. It utilizes the room files created 
in part 1, pulling the data for each room and storing it in its own graph array. Once
the data is retrieved, the game logic begins where the user can navigate from room to
room until they reach the end room.

In addition to the adventure game, there is a second thread that allows the user to
ask for the time.
------------------------------------------------------------------------------------*/
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <assert.h>

//The room struct will hold all of the information about a particular room
struct Room {
		char *name;            //Room name 
		char *type;            //Room type 
		char *connections[6];  //An array of names that represent connections 
		int numConnections;    //The number of connections in the graph
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //Mutex initializer

char directory[256];      //A pointer to the name of the most recent rooms directory
struct Room graph[7];     //This array will hold the graph of 7 linked rooms
char *pathToVictory[100]; //An array that holds the names of the visited rooms
int steps = 0;            //The number of steps the user has taken
int startRoom;            //The index of the start room
int endRoom;              //The index of the end room
int location;             //The index of the room the user is currently in

/*------------------------------------------------------------------------------------
FindNewestDirectory

This function finds the most recent rooms directory (created in part 1) and returns
the name.

Returns: A pointer to a string that contains the name of the most recent directory
------------------------------------------------------------------------------------*/
void FindNewestDirectory() {
	int newestDirTime = -1; // Modified timestamp of newest subdir examined
	char targetDirPrefix[32] = "merrillc.rooms."; // Prefix we're looking for
	memset(directory, '\0', sizeof(directory));

	DIR* dirToCheck;           //Holds the directory we're starting in
	struct dirent *fileInDir;  //Holds the current subdir of the starting dir
	struct stat dirAttributes; //Holds information we've gained about subdir
	
	//Open up the directory this program was run in
	dirToCheck = opendir("."); 

	//Make sure the current directory could be opened
	if (dirToCheck > 0) 
	{
		//Check each entry in the current directory
		while ((fileInDir = readdir(dirToCheck)) != NULL) 
		{
			//If entry has prefix
			if (strstr(fileInDir->d_name, targetDirPrefix) != NULL) 
			{
				//Get attributes of the entry
				stat(fileInDir->d_name, &dirAttributes); 

				//If this time is bigger
				if ((int)dirAttributes.st_mtime > newestDirTime) 
				{
					//Update the newest directory
					newestDirTime = (int)dirAttributes.st_mtime;
					memset(directory, '\0', sizeof(directory));
					strcpy(directory, fileInDir->d_name);
				}
			}
		}
	}
	//Close the directory 
	closedir(dirToCheck);
}

/*------------------------------------------------------------------------------------
GetRoomName

This function returns the name of the room with the passed index. 

Input: An int value representing the index of the desired room
Returns: A pointer to a string that contains the name of the room with the passed index
------------------------------------------------------------------------------------*/
char *GetRoomName (int roomNum) {
	FILE *roomFile;      //Holds the room file
	char fileName[64],   //The name of the room file
	     room[20],       //Will hold the first word in the line "ROOM NAME: <NAME>"
		 specifier[20],  //Will hold the second word in the line "ROOM NAME: <NAME>"
		 line[64];       //Will hold the line "ROOM NAME: <NAME>"
	
	//Allocate a pointer that will hold the name in "ROOM NAME: <NAME>"
	char *name;
	name = (char*)malloc(64);
	
	//Print the file name to fileName
	sprintf(fileName, "./%s/room%d.txt", directory, roomNum);
	
	//Open the room file
	roomFile = fopen(fileName, "r");
	
	//Get the first line
	fgets(line, 64, roomFile);
	
	//Scan the first line and store its contents into the three char arrays
	sscanf(line, "%s %s %s", room, specifier, name);
	
	//Close the room file
	fclose(roomFile);
	
	//Return a pointer to the room name
	return name;
}

/*------------------------------------------------------------------------------------
GetRoomType

This function returns the type of the room with the passed index. 

Input: An int value representing the index of the desired room
Returns: A pointer to a string that contains the type of the room with the passed index
------------------------------------------------------------------------------------*/
char *GetRoomType (int roomNum) {
	FILE *roomFile;     //Holds the room file
	int typeFound = 0;  //Bool value
	char fileName[64],  //The name of the room file
	     room[20],      //Will hold the first word in the line "ROOM TYPE: <TYPE>"
		 specifier[20], //Will hold the second word in the line "ROOM TYPE: <TYPE>"
		 line[64];      //Will hold the line "ROOM TYPE: <TYPE>"
	
	//Allocate a pointer that will hold the type in "ROOM TYPE: <TYPE>"
	char *type;
	type = (char*)malloc(64);
	
	//Print the file name to fileName
	sprintf(fileName, "./%s/room%d.txt", directory, roomNum);
	
	//Open the room file
	roomFile = fopen(fileName, "r");
	
	//Skip the first line (the name line)
	fgets(line, 64, roomFile); 
	
	//Skip through the connection lines
	while (typeFound == 0) {
		fgets(line, 64, roomFile); 
		sscanf(line, "%s %s %s", room, specifier, type);
		
		//If the first word in the line doesn't start with 'C', the type line has been
		//reached
		if (room[0] != 'C')
			typeFound = 1;
	} 
	
	//Close the room file
	fclose(roomFile);
	
	//Return a pointer to the room type
	return type;
}

/*------------------------------------------------------------------------------------
GetConnection

This function returns the a the name of a connection to a room. 

Input: An int value representing the index of the desired room
	   An int value representing the index of the desired connection
Returns: A pointer to a string that contains the name of the desired connection
------------------------------------------------------------------------------------*/
char *GetConnection (int roomNum, int connectionNum) {
	FILE *roomFile;      //Holds the room file
	char fileName[64],   //The name of the room file
	     room[20],       //Will hold the first word in the line "CONNECTION <#>: <NAME>"
		 specifier[20],  //Will hold the second word in the line "CONNECTION <#>: <NAME>"
		 line[64];       //Will hold the line "CONNECTION <#>: <NAME>"
	int endReached = 0;  //Bool value
	int i;
	
	//Allocate a pointer that will hold the name in "CONNECTION <#>: <NAME>"
	char *connection;
	connection = (char*)malloc(64);
	
	//Print the file name to fileName
	sprintf(fileName, "./%s/room%d.txt", directory, roomNum);
	
	//Open the room file
	roomFile = fopen(fileName, "r");
	
	//Skip the first line (the name line)
	fgets(line, 64, roomFile); 
	
	//Loop through the connection lines until the desired connection is reached
	for(i=0; i<=connectionNum; i++) {
		fgets(line, 64, roomFile); 
		sscanf(line, "%s %s %s", room, specifier, connection);
	}
	
	//Close the room file
	fclose(roomFile);
	
	//Return a pointer to the connection name
	return connection;
}

/*------------------------------------------------------------------------------------
GetNumConnections

This function returns the number of connections a room has.

Input: An int value representing the index of the desired room
Returns: An int value representing the number of connections
------------------------------------------------------------------------------------*/
int GetNumConnections (int roomNum) {
	int numConnections = 0; //Initialize the number of connections to 0
	int typeFound = 0;      //Bool value
	FILE *roomFile;         //Holds the room file
	char fileName[64],      //The name of the room file
	     room[20],          //Will hold the first word in the line "CONNECTION <#>: <NAME>" 
		 specifier[20],     //Will hold the second word in the line "CONNECTION <#>: <NAME>"
		 line[64],          //Will hold the line "CONNECTION <#>: <NAME>"
		 connection[20];    //Will hold the name in the line "CONNECTION <#>: <NAME>"
	
	//Print the file name to fileName
	sprintf(fileName, "./%s/room%d.txt", directory, roomNum);
	
	//Open the room file
	roomFile = fopen(fileName, "r");
	
	//Skip the first line (the name line)
	fgets(line, 64, roomFile); 
	
	//Loop through the connection lines until the type line is reached
	while (typeFound == 0) {
		fgets(line, 64, roomFile); 
		sscanf(line, "%s %s %s", room, specifier, connection);
		
		//If the first letter in the line is not 'C' then we've reached the type line
		if (room[0] != 'C')
			typeFound = 1;
		//Otherwise increase the number of connections
		else
			numConnections++;
	} 
	
	//Close the room file
	fclose(roomFile);
	
	//Return the number of connections
	return numConnections;
}

/*------------------------------------------------------------------------------------
PopulateGraph

This function copies the room file contents into the graph array.
------------------------------------------------------------------------------------*/
void PopulateGraph() {
	int i;
	int j;
	
	//Loop through each room file
	for(i=0;i<7;i++) {
		//Add the room name using GetRoomName()
		graph[i].name = GetRoomName(i);
		
		//Add the room type using GetRoomType()
		graph[i].type = GetRoomType(i);
		
		//Add the number of connections using GetNumConnections()
		graph[i].numConnections = GetNumConnections(i);
		
		//Add each connection name using GetConnection() 
		for(j=0;j<graph[i].numConnections;j++) {
			graph[i].connections[j] = GetConnection(i, j);
		}
	}
}

/*------------------------------------------------------------------------------------
DetermineLocations

Sets the index of the start room, end room and user location.
------------------------------------------------------------------------------------*/
void DetermineLocations() {
	int i;
	
	//Loop through each room in graph
	for(i=0;i<7;i++) {
		//If the type equals START_ROOM, set startRoom and location equal to the index 
		if (strcmp(graph[i].type, "START_ROOM") == 0) {
			startRoom = i;
			location = i;
		}
		//If the type equals END_ROOM, set endRoom equal to the index
		else if (strcmp(graph[i].type, "END_ROOM") == 0)
			endRoom = i;
	}
}

/*------------------------------------------------------------------------------------
DisplayRoomContents

Displays the user's current location and the connections to that location.
------------------------------------------------------------------------------------*/
void DisplayRoomContents () {
	int i;
	
	//Display the current location
	printf("CURRENT LOCATION: %s\n", graph[location].name);
	
	//Display each possible connection
	printf("POSSIBLE CONNECTIONS: ");
	for (i=0; i<graph[location].numConnections; i++) {
		printf("%s", graph[location].connections[i]);
		
		//If this is the last connection, add a period
		if (i == (graph[location].numConnections - 1)) 
			printf(".\n"); 
		//Otherwise add a comma and space
		else
			printf(", ");	
	}
}

/*------------------------------------------------------------------------------------
IsConnection

Determines if the passed name is a connection of the passed room.

Input: A pointer-to-string representing the connection name in question
       An int value representing the index of the room
Returns: True if the passed name is a connection of the passed room, flase otherwise
------------------------------------------------------------------------------------*/
int IsConnection(char *name, int room) {
	int isConnection = 0;               //Bool value
	int n = graph[room].numConnections; //The # of connections to room
	char testName[64];                  //name with an appended "\n" term
	int i;
	
	
	//Loop through each connection to room
	for (i=0; i<n; i++) {
		//Append "\n" to the connection name
		sprintf(testName, "%s\n", graph[room].connections[i]);
		
		//If the testName equals the passed name, it is a connection of room
		if (strcmp(testName, name) == 0) 
			isConnection = 1;	
	}
	
	//Return bool value
	return isConnection;
}

/*------------------------------------------------------------------------------------
GetRoomIndex

Gets the index of the room with the passed name.

Input: A pointer-to-string representing the name of the room
Returns: An int representing the index of the desired room
------------------------------------------------------------------------------------*/
int GetRoomIndex(char *name) {
	char testName[64]; //name with an appended "\n" term
	int index;         //The desired index
	int i;
	
	//Loop through each room until the passed name matches the room name
	for (i=0; i<7; i++) {
		//Append a "\n" to the end of the room name to compare with the passed name
		sprintf(testName, "%s\n", graph[i].name);
		
		//If the testName equals the passed name, store that index
		if (strcmp(testName, name) == 0) 
			index = i;
	}
	
	//Return the room index
	return index;
}

/*------------------------------------------------------------------------------------
TellTime

Writes the current time to a file named currentTime.txt. This function only runs as 
part of the tellTime thread that is executed in the play loop. It utilizes mutex locks
to protect the currentTime.txt file while writing in data. 
------------------------------------------------------------------------------------*/
void* TellTime() {
	FILE *timeFile;         //Points to the time file
	char hourMinSec[12],
		 day[12],
		 month[12],
		 date[12],
		 year[12],
		 unformattedTime[64],
		 formattedTime[64];
	
	//Set t equal to the time
	time_t t;
	t = time(NULL);	
	
	//Set unformatted time equal to ctime()
	sprintf(unformattedTime, ctime(&t));
	
	//Parse the data from unformattedTime
	sscanf(unformattedTime, "%s %s %s %s %s", day, month, date, hourMinSec, year);
	
	//Rearrange the time into the proper format and store it in formattedTime
	sprintf(formattedTime, "%s, %s, %s %s, %s", hourMinSec, day, month, date, year);
	
	//Put a mutex lock on the secondary thread before opening currentTime.txt
	pthread_mutex_lock(&mutex);
	
	//Open currentTime.txt
	timeFile = fopen("currentTime.txt", "w");
	
	//Put the formatted time into currentTime.txt
	fputs(formattedTime, timeFile);
	
	//Close currentTime.txt
	fclose(timeFile);
	
	//Remove the mutex lock
	pthread_mutex_unlock(&mutex);
}

/*------------------------------------------------------------------------------------
Play

This function contains the main game loop. It retrieves user input to navigate through
each room until the END_ROOM is found. 
------------------------------------------------------------------------------------*/
void Play() {
	FILE *timeFile;      //Holds currentTime.txt when the user enters "time"
	char time[64];       //The time read from currentTime.txt
	int memoryRead;      //Test variable for bytes read in by getline
	size_t nBytes = 255; //The number of bytes allowed for getline input
	char *inputString;   //Holds the user input
	inputString = (char *)malloc(256);
	int i;
	
	//Continue to loop until the users location equals the endRoom location
	while (location != endRoom) {		
		//Display the current room name and possible connections
		DisplayRoomContents();
		
		//Promt user to enter a room name
		printf("WHERE TO? >");
		
		//Read in user input
		memoryRead = getline(&inputString, &nBytes, stdin);
		
		//If the user entered "time", run the threads to display time and write time file
		if(strcmp(inputString, "time\n") == 0) {			
			pthread_t tellTime;
			int result;
			
			//Create a second thread called tellTime that executes the TellTime function
			result = pthread_create(&tellTime, NULL, TellTime, NULL);
			assert(result == 0); //Assert that the thread was successfully created
			
			//Wait for the file to be written before continuing
			result = pthread_join(tellTime, NULL);
			
			//Lock the main thread until the secondary thread is done writing the file
			pthread_mutex_lock(&mutex);
			
			//Open currentTime.txt
			timeFile = fopen("currentTime.txt", "r");
			
			//Read the time from the currentTime.txt file
			fgets(time, 64, timeFile);

			//Print the time
			printf("\n%s\n", time);
			
			//Close currentTime.txt
			fclose(timeFile);
			
			//Unlock the main thread
			pthread_mutex_unlock(&mutex);
		}
		//If the input was invalid, return error message
		else if (memoryRead == -1 || IsConnection(inputString, location) != 1) 
			printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
		else {	
			//Update the location
			location = GetRoomIndex(inputString);
			
			//Add current location to pathToVictory
			pathToVictory[steps] = graph[location].name;
			
			//Add 1 to steps
			steps++;
		}
		
		printf("\n");
	}
	
	//Display the congratulatory message
	printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	
	//Diplay the number of steps taken
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
	
	//List the contents of the path to victory
	for (i=0; i<100; i++) 
		if (pathToVictory[i] != 0)
			printf("%s\n", pathToVictory[i]);

	//Free the user input
	free(inputString);
}

/*------------------------------------------------------------------------------------
CleanUp

This function frees all of the allocated memory that was used within the program.
------------------------------------------------------------------------------------*/
void CleanUp() {
	int i, j;
	
	//Loop through all of the graph contents and free all of the pointers
	for(i=0;i<7;i++) {
		free(graph[i].name);
		free(graph[i].type);
		
		for(j=0;j<6;j++) {
			free(graph[i].connections[j]);
		}
	}
}

int main() {
	FindNewestDirectory();  //Find most recent directory
	PopulateGraph();        //Store room file contents in graph
	DetermineLocations();   //Locate the start and end rooms
	Play();                 //Run the game loop
	CleanUp();              //Free allocated memory
	return 0;
}