/********************************************************************************
* Name: Christopher Merrill
* CS 344
* Program 3: Small Shell
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>
#include<unistd.h>

struct sigaction sa;  //Signal action
char* args[513];      //An array of arguments (512 max)
char* line = NULL;    //User input
char* inFile = NULL;  //User-specified input 
char* outFile = NULL; //User-specified output
char* arg;            //Holds a single argument
int status = 0;       //Process status
int fgOnlyMode = 0;   //Whether or no foreground only mode is turned on
int isBG;             //Whether or not a process is running in the background
int argCount;         //The number of passed arguments
int pid;              //Process ID

//Function Definitions
void commandLoop();
void getInput();
void parseArguments();
void checkBGProcesses();
void reset();
void fgOnly();
char* replace(char* str, char* x, char* y);

int main() {	
	//Handle Ctrl+C command by ignoring SIGINT
	sa.sa_handler = SIG_IGN; 
	sigaction(SIGINT, &sa, NULL);
	
	//Handle Ctrl+Z command by running fgOnly function
	signal(SIGTSTP, fgOnly); 
	
	//Start the command loop
	commandLoop();  
    return 0;
}

/********************************************************************************
* commandLoop
*
* This function handles all of the logic necessary for running a user-specified
* command. It consists of a loop that retrieves input from the user, parses each
* of the arguments and runs the command. It also determines if the command passed
* is built-in (cd, status, exit), a comment, or a regular bash command. It 
* continues to loop until the user enters the "exit" command.
*********************************************************************************/
void commandLoop() {
	char pidString[] = "";
	int exited = 0;
	int file;
	int i;
	
	//Start the main loop that will handle commands from the user
	while (!exited) {
		reset();           //Reset shell for next command
		getInput();        //Get input from the user
		parseArguments();  //Parse each of the arguments
		
		//Store the PID as a string
		sprintf(pidString, "%d", getpid());
		
		//Look for any cases of $$ in args and replace it with the PID
		for (i=0; i<argCount; i++) {
			replace(args[i], "$$", pidString);
		}

		//Do nothing for a comment or NULL command
		if (!(strncmp(args[0], "#", 1)) || args[0] == NULL){}
		//Check for the "exit" command
		else if (strcmp(args[0], "exit") == 0) { 
			exited = 1; //End the while loop
			exit(0);    //Exit status 0
		} 
		//Check for the "status" command
		else if (strcmp(args[0], "status") == 0) { 
			//Print the exit status
			if (WIFEXITED(status)) {
				printf("EXIT STATUS: %d\n", WEXITSTATUS(status));
				fflush(stdout);
			}
			//Or print the terminating signal
			else {
				printf("TERMINATING SIGNAL %d\n", status);
				fflush(stdout);
			}								
		}
		//Check for the "cd" command
		else if (strcmp(args[0], "cd") == 0) { 
			//If no directory is specified, go to the home directory
			if (args[1] == NULL) 
				chdir(getenv("HOME"));
			//Otherwise go to the specified directory
			else 
				chdir(args[1]);
		}
		//If any other command is entered, fork to a new process
		else { 
			//Fork the process
			pid = fork(); 
			
			//Child process
			if (pid == 0) {  
				//If the process is not in the background, it can be interrupted
				if(!isBG) { 
					sa.sa_handler = SIG_DFL; 
					sa.sa_flags = 0;         
					sigaction(SIGINT, &sa, NULL);
				}
				//Check if the user specified an input file
				if (inFile != NULL) { 
					//Open the file for reading
					file = open(inFile, O_RDONLY);
					
					//Check for a valid file
					if (file == -1) {
						fprintf(stderr, "INVALID FILE: %s\n", inFile);
						fflush(stdout);
						exit(1);
					}
					//Redirect the input
					else if (dup2(file, 0) == -1) { 
						//Notify user if there was a redirect error
						fprintf(stderr, "INPUT REDIRECT ERROR");
						fflush(stdout);
						exit(1);
					}
					//Close file
					close(file);
				} 
				//If the process is in the background and input is not specified
				else if (isBG) {
					//Redirect input to /dev/null 
					file = open("/dev/null", O_RDONLY);
					
					//Notify the user if the file could not be opened
					if (file == -1) {
						fprintf(stderr, "FILE OPEN ERROR");
						fflush(stdout);
						exit(1);
					}
					//Redirect input
					else if (dup2(file, 0) == -1) { 
						//Notify user if there was a redirect error
						fprintf(stderr, "INPUT REDIRECT ERROR");
						fflush(stdout);
						exit(1);
					}
					//Close file 	
					close(file);
				}
				
				//Check if the user specified an output file
				if (outFile != NULL) { 
					//Open the file for reading
					file = open(outFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					
					//Check for a valid file
					if (file == -1) {
						fprintf(stderr, "INVALID OUTPUT FILE: %s\n", outFile);
						fflush(stdout);
						exit(1);
					}
					//Redirect the output
					if (dup2(file, 1) == -1) { 
						//Notify user if there was a redirect error
						fprintf(stderr, "OUTPUT REDIRECT ERROR");
						fflush(stdout);
						exit(1);
					}
					//Close file 
					close(file);
				}

				//Execute the command
				if (execvp(args[0], args)) {
					//Throw error if the command wasn't recognized
					fprintf(stderr, "COMMAND UNKNOWN: %s\n",args[0]);
					fflush(stdout);
					exit(1);
				}
			}
			//Check for a fork error
			else if (pid < 0) { 
				//Throw error 
				fprintf(stderr, "UNABLE TO FORK");
				fflush(stdout);
				status = 1;
				break;
			}
			//Parent process
			else { 
				//If its not in the background, wait for the foreground process
				if (!isBG) { 
					do {
						waitpid(pid, &status, 0);
					} while (!WIFEXITED(status) && !WIFSIGNALED(status));
				} 
				//Otherwise print the background processes PID
				else {
					printf("BACKGROUND PID: %d\n", pid);
					fflush(stdout);
				}
			}	
		}
		//Handle background processes
		checkBGProcesses();
	}    
}

/********************************************************************************
* getInput
*
* This function prints the prompt (:) and retrieves a command from the user using
* getline. 
*********************************************************************************/
void getInput() {
	//Print prompt
	printf(": ");     
	fflush(stdout);     

	//Read in a command line
	ssize_t size = 0;
	getline(&line, &size, stdin);
}

/********************************************************************************
* parseArguments
*
* This function stores each of the passed arguments into the args array. 
*********************************************************************************/
void parseArguments() {
	argCount = 0;
	
	//Grab the first argument
	arg = strtok(line, "  \n"); 
	
	//Loop through all remaining arguments
	while (arg != NULL) {
		//If the argument is an input file
		if (strcmp(arg, "<") == 0) {
			//Store the file name in inFile and get the next arg
			arg = strtok(NULL, " \n");
			inFile = strdup(arg);
			arg = strtok(NULL, " \n");
		}
		//If the argument is an output file
		else if (strcmp(arg, ">") == 0) {
			//Store the file name in outFile and get the next arg
			arg = strtok(NULL, " \n");
			outFile =  strdup(arg); 
			arg = strtok(NULL, " \n");
		}
		//If the process should be backgrounded
		else if (strcmp(arg, "&") == 0) {
			//If foreground only mode is off, this process should 
			//run in the background.
			if (fgOnlyMode == 0) {
				//Update isBG
				isBG = 1; 
				break;
			}
			break;
		} 
		//Store argument in the args array and get the next arg
		else {
			args[argCount] = strdup(arg);
			arg = strtok(NULL, " \n");
			argCount++; 
		}
	}

	//Last arg should be NULL
	args[argCount] = NULL;
}

/********************************************************************************
* checkBGProcesses
*
* Determines the status of processes running in the background.
*********************************************************************************/
void checkBGProcesses() {
	pid = waitpid(-1, &status, WNOHANG);
	
	//Check to see if any processes have completed
	while (pid > 0) {
		//Notify the user if the process has completed
		printf("BACKGROUND PID COMPLETE: %d\n", pid);
		
		//If the process ended naturally, display the exit status
		if (WIFEXITED(status)) { 
			printf("EXIT STATUS: %d\n", WEXITSTATUS(status));
			fflush(stdout);
		}
		//Otherwise display the terminating signal
		else { 
			printf("TERMINATING SIGNAL: %d\n", status);
			fflush(stdout);
		}

		pid = waitpid(-1, &status, WNOHANG);
	}
}

/********************************************************************************
* reset
*
* This function resets the args array, input/output files and BG parameter in
* preparation for the next user command. 
*********************************************************************************/
void reset() {
	int i;
	
	//Empty the argument array
	for (i = 0; i < argCount; i++) {
		args[i] = NULL;
	}
	
	//Set files to null to be reused for future commands
	inFile = NULL;
	outFile = NULL;
	
	//Set isBG back to zero
	isBG = 0;
}

/********************************************************************************
* fgOnly
*
* Handles the case when the Ctrl+Z command is entered by the user. It turns 
* foreground only mode off and on. 
*********************************************************************************/
void fgOnly() {
	//If foreground only mode is off, turn it on
	if (fgOnlyMode == 0) {
		printf("Entering Foreground Only Mode (& is ignored)\n");
		fflush(stdout);
		fgOnlyMode = 1;
	}
	//If foreground only mode is on, turn it off
	else {
		printf("Exiting Foreground Only Mode\n");
		fflush(stdout);
		fgOnlyMode = 0;
	}
}

/********************************************************************************
* replace
*
* Replaces characters in a string. Used to replace any instance of $$ with the 
* PID. 
*********************************************************************************/
char* replace(char* str, char* x, char* y)
{
	char* p;                //Iterator
    int len  = strlen(str); //Length of the passed string
    int lenX = strlen(x);   //Length of substring x
	int lenY = strlen(y);   //Length of substring y
	
	//Loop through the passed string and replace any instance of x with y
    for (p = str; p = strstr(p, x); ++p) {
		//Shift the end of the string if x and y are different lengths
        if (lenX != lenY) 
            memmove(p+lenY, p+lenX,
                len - (p - str) + lenY);
        memcpy(p, y, lenY);
    }
	
	//Return the updated string
    return str;
}