/*************************************************
Christopher Merrill                              * 
CS344                                            *
Program 4                                        *
                                                 *
This file handles decryption on the server side. *
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//Error function used for reporting issues
void error(const char *msg) { perror(msg); exit(1); } 

int main(int argc, char *argv[]) {
	int listenSocketFD, establishedConnectionFD, portNumber, receiveText, pid, status, i;
	socklen_t sizeOfClientInfo;
	struct sockaddr_in serverAddress, clientAddress;
	
	//Check usage & args
	if (argc < 2) {fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1);} 

	//Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	//Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket\n");

	//Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding\n");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections
	
	//Infinte loop to handle incoming connections
	while (1) {
		int encryptedSize, encryptedLength, keySize, keyLength, count, rec, plainVal, keyVal, encryptedVal;
		char buffer[1024];
		char* encryptedText;
		char* keyText;
	
		//Accept a connection, blocking if one is not available until one connects
		sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
		establishedConnectionFD = accept(listenSocketFD, NULL, NULL); // Accept
		if (establishedConnectionFD < 0) error("ERROR on accept\n");
		
		//Fork a new process
		pid = fork();
		if (pid < 0) error("ERROR: Unable to fork");
		//Child Process
		else if (pid == 0) {
			//Confirm that otp_dec is trying to connect
			receiveText = htonl(0);
			if (send(establishedConnectionFD, &receiveText, sizeof(receiveText), 0) == -1) error("ERROR: Failed to receive text from client\n");
			
			//Receive encrypted text and key text size
			if (recv(establishedConnectionFD, &encryptedSize, sizeof(encryptedSize), 0) == -1) error("ERROR: Failed to receive encrypted text size from client\n");
			else if (encryptedSize == 0) error("ERROR: encrypted text size is 0\n");
			if (recv(establishedConnectionFD, &keySize, sizeof(keySize), 0) == -1) error("ERROR: Failed to receive key text size from client\n");
			else if (keySize == 0) error("ERROR: Key text size is 0\n");
			
			//Set the encrypted text and key text length
			encryptedLength = ntohl(encryptedSize);
			keyLength = ntohl(keySize);
			
			//RECIEVE ENCRYPTED TEXT
			encryptedText = malloc(sizeof(char) * encryptedLength);
			memset(encryptedText, '\0', encryptedLength);
			count = 0;
			
			//Continue looping until entire file is received
			while (count <= encryptedLength) {
				//Clear the buffer
				memset((char*)buffer, '\0', sizeof(buffer));
				
				//Receive encrypted text
				rec = recv(establishedConnectionFD, &buffer, 1024, 0);
				if (rec == -1) {error("ERROR: Failed to receive encrypted text\n"); break;}
				else if (rec == 0) {
					//Break if there is still more to receive
					if (count < encryptedLength) break;
				}
				//Otherwise concatenate the string
				else strncat(encryptedText, buffer, (rec - 1));
				
				//Increment count by the length that has been received so far
				count += (rec - 1);
			}
			
			//Add null terminator
			encryptedText[encryptedLength - 1] = '\0';
			
			//RECIEVE KEY TEXT
			keyText = malloc(sizeof(char) * keyLength);
			memset((char*)buffer, '\0', sizeof(buffer));
			memset(keyText, '\0', keyLength);
			count = 0;
			
			//Continue looping until entire file is received
			while (count <= keyLength) {
				//Clear the buffer
				memset((char*)buffer, '\0', sizeof(buffer));
				
				//Receive plain text
				rec = recv(establishedConnectionFD, &buffer, 1024, 0);
				if (rec == -1) {error("ERROR: Failed to receive key text\n"); break;}
				//Break if end of file is reached
				else if (rec == 0) break;
				//Concatenate key text string
				else strncat(keyText, buffer, (rec - 1));
				
				//Increment count by the length that has been received so far
				count += (rec - 1);
			}
			
			//Add null terminator
			keyText[keyLength - 1] = '\0';
			
			//Decrypt each character of encrypted text
			for (i = 0; i < encryptedLength - 1; i++) {
				//Transform encrypted text character to int
				if (encryptedText[i] != ' ') encryptedVal = encryptedText[i] - 65;
				else encryptedVal = 26; //space case
				
				//Transform key text character to int
				if (keyText[i] != ' ') keyVal = keyText[i] - 65;
				else keyVal = 26; //space case
				
				//Decrypted value is difference of encrypted and key values
				plainVal = encryptedVal - keyVal;
				//If decrypted value is negative, add 27
				if (plainVal < 0) plainVal += 27;
				
				//Replace each encrypted text character with the decrypted character
				if (plainVal != 26) encryptedText[i] = 'A' + (char)plainVal;
				else encryptedText[i] = ' '; //space case
			}
			
			//SEND PLAIN STRING BACK TO CLIENT
			count = 0;
			
			//Continue to loop until entire file has been sent
			while (count <= encryptedLength) {
				char plainString[1024];
				
				//Copy encrypted text to plain string
				strncpy(plainString, &encryptedText[count], 1023);
				plainString[1024] = '\0'; //add null terminator
				if (send(establishedConnectionFD, &plainString, 1024, 0) == -1) error("Error: Unable to send encrypted string\n");
				
				//Increment count by the length of text sent
				count += 1023;
			}
			
			//Free memory
			free(encryptedText);
			free(keyText);
			
		}
		//Parent Process
		else {
			//Close connection to the client
			close(establishedConnectionFD);
			
			//Wait for unfinished children
			do {
				waitpid(pid, &status, 0);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}	
	}
	
	//Close the socket
	close(listenSocketFD);
	
	return 0;
}
