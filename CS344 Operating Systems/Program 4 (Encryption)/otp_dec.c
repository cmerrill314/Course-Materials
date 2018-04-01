/*************************************************
Christopher Merrill                              * 
CS344                                            *
Program 4                                        *
                                                 *
This file handles decryption on the client side. *
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
	int socketFD, portNumber, encryptedLength, keyLength, encryptedTextFD, keyFD, sendEncryptedTextLength, sendKeyTextLength,
		confirmationNumber, confirmed, rec, count, i;
	char buffer[1024], sendEncryptedText[1024], sendKeyText[1024];
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char* plainText; 
	char* keyText; 
	char* encryptedText;
		
	//Check usage & args
	if (argc < 4) { fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(0);} 
	
	//Open encrypted text and key files 
	encryptedTextFD = open(argv[1], O_RDONLY);
	keyFD = open(argv[2], O_RDONLY);
	
	//Check that there was not an error opening the files
	if (encryptedTextFD == -1 || keyFD == -1) {fprintf(stderr, "ERROR: Unable to open files\n"); exit(1);}
	
	//Check that the key file is larger than the encrypted text file
	encryptedLength = lseek(encryptedTextFD, 0, SEEK_END);
	keyLength = lseek(keyFD, 0, SEEK_END);
	if (keyLength < encryptedLength) {fprintf(stderr, "ERROR: Key too short!\n"); exit(1);}
	
	//Create strings for encrypted text and key text
	encryptedText = malloc(sizeof(char) * encryptedLength);
	keyText = malloc(sizeof(char) * keyLength);
	
	//Set file pointers to the beginning of each file
	lseek(encryptedTextFD, 0, SEEK_SET);
	lseek(keyFD, 0, SEEK_SET);
	
	//Read each text file into the created strings
	if (read(encryptedTextFD, encryptedText, encryptedLength) == -1) {fprintf(stderr, "ERROR: Failed to read encrypted text\n"); exit(1);}
	if (read(keyFD, keyText, keyLength) == -1) {fprintf(stderr, "ERROR: Failed to read key text\n"); exit(1);}
	
	//Add null terminators
	encryptedText[encryptedLength - 1] = '\0';
	keyText[keyLength - 1] = '\0';
	
	//Check for invalid characters in encrypted text
	for (i = 0; i < encryptedLength - 1; i++) {
		if (isalpha(encryptedText[i]) || isspace(encryptedText[i])) {}//Do nothing if valid}
		else {fprintf(stderr, "ERROR: Encrypted Text Contains Invalid Character\n"); exit(1);}
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
	
	//Connect to otp_dec_d server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) 
		error("CLIENT: ERROR connecting");
	
	//Send encrypted text and key text length to server
	sendEncryptedTextLength = htonl(encryptedLength);
	sendKeyTextLength = htonl(keyLength);

	//Receive confirmation number
	if((rec = recv(socketFD, &confirmationNumber, sizeof(confirmationNumber), 0)) <= 0) 
		error("CLIENT: ERROR: Failed to receive confirmation number.\n");

	//Verify confirmation number
	confirmed = ntohl(confirmationNumber);

	if (confirmed != 0) error("ERROR: otp_dec cannot use otp_enc_d %d\n");
	
	//Assure that the lengths were sent
	if(send(socketFD, &sendEncryptedTextLength, sizeof(sendEncryptedTextLength), 0) == -1) {fprintf(stderr, "Failed to send plain text length\n"); exit(1);}
	if(send(socketFD, &sendKeyTextLength, sizeof(sendKeyTextLength), 0) == -1) {fprintf(stderr, "Failed to send key text length\n"); exit(1);}
	
	//SEND ENCRYPTED TEXT TO SERVER
	count = 0;
	
	//Continue looping until the entire file is sent
	while (count <= encryptedLength) {
		//Copy encrypted text into the send encrypted text string
		strncpy(sendEncryptedText, &encryptedText[count], 1023);
		sendEncryptedText[1024] = '\0'; //Add a null terminator
		
		//Send encrypted text
		if (send(socketFD, &sendEncryptedText, 1024, 0) == -1) {fprintf(stderr, "Failed to send plain text\n"); exit(1);}
		
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
		
		//Send key text
		if (send(socketFD, &sendKeyText, 1024, 0) == -1) {fprintf(stderr, "Failed to send key text\n"); exit(1);}
		
		//Increment count by the length of the sent text
		count += 1023;
	}
	
	//RECEIVE PLAIN TEXT FROM SERVER
	plainText = malloc(sizeof(char) * encryptedLength);
	memset(plainText, '\0', encryptedLength);
	count = 0;
	rec = 0;
	
	//Continue looping until the entire file is received
	while (count < encryptedLength) {
		//Clear the buffer and recieve the text
		memset((char*)buffer, '\0', sizeof(buffer));
		rec = recv(socketFD, buffer, 1024, 0);
		
		//Check for failed recv
		if (rec == -1) {fprintf(stderr, "Failed to receive plain text\n"); exit(1);}
		else if (rec == 0) {fprintf(stderr, "Failed to receive plain text\n"); exit(1);}
		//If successful, concatenate the plain text string
		else {strncat(plainText, buffer, (rec - 1));}
		
		//Increment count by the length of the received text
		count += (rec - 1);
	}
	
	//Add null terminator to plain text and print it
	plainText[encryptedLength - 1] = '\0';
	printf("%s\n", plainText);
	
	//Free memory
	free(encryptedText);
	free(keyText);
	free(plainText);
	
	//Close the socket
	close(socketFD); 
	
	return 0;
}
