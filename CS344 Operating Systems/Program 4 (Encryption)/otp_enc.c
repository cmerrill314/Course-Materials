/*************************************************
Christopher Merrill                              * 
CS344                                            *
Program 4                                        *
                                                 *
This file handles encryption on the client side. *
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

//Error function used for reporting issues
void error(const char *msg) { perror(msg); exit(0); } 

int main(int argc, char *argv[]) {
	int socketFD, portNumber, plainLength, keyLength, plainTextFD, keyFD, sendPlainTextLength, sendKeyTextLength, rec, count, i;
	char buffer[1024], sendPlainText[1024], sendKeyText[1024];
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char* plainText; 
	char* keyText; 
	char* encryptedText;
		
	//Check usage & args
	if (argc < 4) { fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(0);} 
	
	//Open plain text and key files 
	plainTextFD = open(argv[1], O_RDONLY);
	keyFD = open(argv[2], O_RDONLY);
	
	//Check that there was not an error opening the files
	if (plainTextFD == -1 || keyFD == -1) {fprintf(stderr, "ERROR: Unable to open files\n"); exit(1);}
	
	//Check that the key file is larger than the plain text file
	plainLength = lseek(plainTextFD, 0, SEEK_END);
	keyLength = lseek(keyFD, 0, SEEK_END);
	if (keyLength < plainLength) {fprintf(stderr, "ERROR: Key too short!\n"); exit(1);}
	
	//Create strings for plain text and key text
	plainText = malloc(sizeof(char) * plainLength);
	keyText = malloc(sizeof(char) * keyLength);
	
	//Set file pointers to the beginning of each file
	lseek(plainTextFD, 0, SEEK_SET);
	lseek(keyFD, 0, SEEK_SET);
	
	//Read each text file into the created strings
	if (read(plainTextFD, plainText, plainLength) == -1) {fprintf(stderr, "ERROR: Failed to read plain text (encryption)\n"); exit(1);}
	if (read(keyFD, keyText, keyLength) == -1) {fprintf(stderr, "ERROR: Failed to read key text (encryption)\n"); exit(1);}
	
	//Add null terminators
	plainText[plainLength - 1] = '\0';
	keyText[keyLength - 1] = '\0';
	
	//Check for invalid characters in plain text
	for (i = 0; i < plainLength - 1; i++) {
		if (isalpha(plainText[i]) || isspace(plainText[i])) {}//Do nothing if valid}
		else {fprintf(stderr, "ERROR: Plain Text Contains Invalid Character\n"); exit(1);}
	}
		
	//Check for invalid characters in key text
	for (i = 0; i < keyLength - 1; i++) {
		if (isalpha(keyText[i]) || isspace(keyText[i])) {}//Do nothing if valid
		else {fprintf(stderr, "ERROR: Key Text Contains Invalid Character\n"); exit(1);}
	}
		
	//Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(1); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address
	
	//Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); //Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	//Connect to otp_enc_d server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
		error("CLIENT: ERROR connecting");
	
	//Send plain text and key text length to server
	sendPlainTextLength = htonl(plainLength);
	sendKeyTextLength = htonl(keyLength);
	
	//Assure that the lengths were sent
	if(send(socketFD, &sendPlainTextLength, sizeof(sendPlainTextLength), 0) == -1) {fprintf(stderr, "Failed to send plain text length\n"); exit(1);}
	if(send(socketFD, &sendKeyTextLength, sizeof(sendKeyTextLength), 0) == -1) {fprintf(stderr, "Failed to send key text length\n"); exit(1);}
	
	//SEND PLAIN TEXT TO SERVER
	count = 0;
	
	//Continue looping until the entire file is sent
	while (count <= plainLength) {
		//Copy plain text into the send plain text string
		strncpy(sendPlainText, &plainText[count], 1023);
		sendPlainText[1024] = '\0'; //Add a null terminator
		
		//Send plain text
		if (send(socketFD, &sendPlainText, 1024, 0) == -1) {fprintf(stderr, "Failed to send plain text\n"); exit(1);}
		
		//Increment count by the length of the sent text
		count += 1023;
	}
	
	//SEND KEY TEXT TO SERVER
	count = 0;
	
	//Continue looping until the entire file is sent
	while (count <= keyLength) {
		//Copy key text into the send key text string{
		strncpy(sendKeyText, &keyText[count], 1023);
		sendKeyText[1024] = '\0'; //Add a null terminator
		
		//Send plain text
		if (send(socketFD, &sendKeyText, 1024, 0) == -1) {fprintf(stderr, "Failed to send key text\n"); exit(1);}
		
		//Increment count by the length of the sent text
		count += 1023;
	}
	
	//RECEIVE ENCRYPTED TEXT FROM SERVER
	encryptedText = malloc(sizeof(char) * plainLength);
	memset(encryptedText, '\0', plainLength);
	count = 0;
	rec = 0;
	
	//Continue looping until the entire file is received
	while (count < plainLength) {
		//Clear the buffer and recieve the text
		memset((char*)buffer, '\0', sizeof(buffer));
		rec = recv(socketFD, buffer, 1024, 0);
		
		//Check for failed recv
		if (rec == -1) {fprintf(stderr, "Failed to receive encrypted text\n"); exit(1);}
		else if (rec == 0) {fprintf(stderr, "Failed to receive encrypted text\n"); exit(1);}
		//If successful, concatenate the encrypted text string
		else {strncat(encryptedText, buffer, (rec - 1));}
		
		//Increment count by the length of the received text
		count += (rec - 1);
	}
	
	//Add null terminator to encrypted text and print it
	encryptedText[plainLength - 1] = '\0';
	printf("%s\n", encryptedText);
	
	//Free memory
	free(plainText);
	free(keyText);
	free(encryptedText);
	
	//Close the socket
	close(socketFD); 
	
	return 0;
}
