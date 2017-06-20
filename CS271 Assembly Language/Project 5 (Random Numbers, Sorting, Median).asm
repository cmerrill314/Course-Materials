; Christopher Merrill
; merrillc@oregonstate.edu
; CS271-400
; Program #5
; Due 3/5/2017

;---------------------------------------------------------------------------------------------------------------
;                                         SORTING RANDOM NUMBERS
;
; This program generates a list of random numbers. It then displays the median of the list, sorts the list, and 
; displays the sorted contents. The user specifies the number of random integers they wish to generate in the 
; range [min, max]. The random numbers will generate in the range [lo, hi]. 
;---------------------------------------------------------------------------------------------------------------

INCLUDE Irvine32.inc

.data
max        DWORD 200            ;The upper limit of valid user entries
min        DWORD 10             ;The lower limit of valid user entries
hi         DWORD 999            ;The highest possible random number value
lo         DWORD 100            ;The lowest possible random number value
request    DWORD ?              ;The user's requested number of random numbers
array      DWORD 800 DUP(?)     ;Holds the random integers that will be sorted

;Strings:
header       BYTE "Programming Assignment #5: Sorting Random Integers",0dh,0ah,0
author       BYTE "by Christopher Merrill",0dh,0ah,0
instruction1 BYTE "How many random numbers would you like to generate?",0dh,0ah,0
instruction2 BYTE "Please stick to the range [10, 200]",0dh,0ah,0 
instruction3 BYTE "Enter a value: ",0
invalid      BYTE "Oops, make sure you enter an integer value that is between 10 and 200...",0dh,0ah,0 
titleOne     BYTE "--------------------- UNSORTED LIST ---------------------",0dh,0ah,0 
titleTwo     BYTE "---------------------- SORTED LIST ----------------------",0dh,0ah,0 
median       BYTE "MEDIAN VALUE: ",0
threeSpaces  BYTE "   ",0

.code
main PROC

	CALL Randomize            ;Seed the random number generator
	
	PUSH OFFSET instruction2  ;Pass the second line of instructions to the Introduction procedure
	PUSH OFFSET instruction1  ;Pass the first line of instructions to the Introduction procedure
	PUSH OFFSET author        ;Pass the author information to the Introduction procedure
	PUSH OFFSET header        ;Pass the header to the Introduction procedure
	CALL Introduction         ;Display the introduction 
	
	PUSH max                  ;Pass the max number of random numbers to the GetData procedure
	PUSH min                  ;Pass the min number of random numbers to the GetData procedure
	PUSH OFFSET invalid       ;Pass the invalid entry message to the GetData procedure
	PUSH OFFSET instruction3  ;Pass the third instruction to the GetData procedure
	PUSH OFFSET request       ;Pass request (by reference) to the GetData procedure
	CALL GetData              ;Retrieve a valid integer from the user
	
	PUSH hi                   ;Pass the upper limit of random number values to the FillArray procedure
	PUSH lo                   ;Pass the lower limit of random number values to the FillArray procedure
	PUSH OFFSET array         ;Pass the empty array to the FillArray procedure
	PUSH request              ;Pass the users request to the FillArray procedure
	CALL FillArray            ;Fill the array with random numbers
	
	PUSH OFFSET threeSpaces   ;Pass blank spaces (for spacing between values) to the DisplayList procedure
	PUSH OFFSET titleOne      ;Pass the first title to the DisplayList procedure
	PUSH OFFSET array         ;Pass the array to the DisplayList procedure
	PUSH request              ;Pass the users request to the DisplayList procedure
	CALL DisplayList          ;Display the unsorted list of random numbers
	
	PUSH OFFSET array         ;Pass the array to the SortList procedure
	PUSH request              ;Pass the users request to the SortList procedure
	CALL SortList             ;Sort the list of random numbers in descending order
	
	PUSH OFFSET median        ;Pass the median string to the DisplayMedian procedure
	PUSH OFFSET array         ;Pass the array to the DisplayMedian procedure
	PUSH request              ;Pass the users request to the DisplayMedian procedure
	CALL DisplayMedian        ;Calculate and display the median value
	
	PUSH OFFSET threeSpaces   ;Pass blank spaces (for spacing between values) to the DisplayList procedure
	PUSH OFFSET titleTwo      ;Pass the second title to the DisplayList procedure
	PUSH OFFSET array         ;Pass the array to the DisplayList procedure
	PUSH request              ;Pass the users request to the DisplayList procedure
	CALL DisplayList          ;Display the sorted list of random numbers
	
	exit                      ;Exit the program
	
main ENDP
;---------------------------------------------------------------------------------------------------------------
;                                               Introduction
;
; Displays the program title, programmer name and initial user instructions. 
;
; Recieves: [ebp + 8]  = program title
;           [ebp + 12] = author information
;			[ebp + 16] = first instruction
;			[ebp + 20] = second instruction
;			
; Returns: N/A 
;---------------------------------------------------------------------------------------------------------------
Introduction PROC
	PUSH ebp               
	MOV ebp, esp
	PUSHAD                 ;Save registers

	MOV edx, [ebp + 8]     ;Display program title
	CALL WriteString
	
	MOV	edx, [ebp + 12]    ;Display programmer's name
	CALL WriteString
	CALL Crlf
	
	MOV	edx, [ebp + 16]    ;Display the first instruction line
	CALL WriteString
	
	MOV	edx, [ebp + 20]    ;Display the second instruction line
	CALL WriteString
	CALL Crlf
	
	POPAD                  ;Restore registers and return
	POP ebp
	RET 16
Introduction ENDP

;---------------------------------------------------------------------------------------------------------------
;                                                   GetData
;
; Gets an integer from the user, in the range [10, 200]. The integer is then validated and stored in request. If
; the user enters an invalid value, they will be prompted to try again until a valid integer is entered.
;
; Recieves: [ebp + 8]  = reference to request
;           [ebp + 12] = instructions to enter an integer value
;			[ebp + 16] = invalid entry message
;			[ebp + 20] = the lower limit of valid entries
;           [ebp + 24] = the upper limit of valid entries
;			
; Returns: A valid integer stored in the variable "request"
;---------------------------------------------------------------------------------------------------------------
GetData PROC
	PUSH ebp     	     
	MOV ebp, esp
	PUSHAD               ;Save registers

readInput:
	MOV edx, [ebp + 12]  
	CALL WriteString     ;Display user instructions
	CALL ReadDec         ;Read in user input
	
	JO invalidEntry      ;Jump to invalidEntry if the overflow flag is set (indicating non-integer entry)
	MOV edx, [ebp + 20]  
	CMP eax, edx         ;Compare the entered value to the lower limit 
	JL invalidEntry      ;Jump to invalid entry if the entered value is below the lower limit
	MOV edx, [ebp + 24]
	CMP eax, edx         ;Compare the entered value to the upper limit
	JLE setValue         ;Jump to setValue if the entered value is less than or equal to the upper limit
	
invalidEntry:
	MOV edx, [ebp + 16]  ;Display the invalid message
	CALL WriteString
	JMP readInput         ;Jump to readInput to ask the user to enter another value

setValue:
	MOV ebx, [ebp + 8]   ;Move the address of request into ebx
	MOV [ebx], eax       ;Store the validated entry in request

	POPAD                ;Restore registers
	POP ebp
	RET 20
GetData ENDP

;---------------------------------------------------------------------------------------------------------------
;                                                  FillArray
;
; Fills "array" with the desired number of random numbers. Each number is generated to be within the range 
; [lo, hi]. 
;
; Recieves: [ebp + 8]  = request (the user's desired number of random integers)
;           [ebp + 12] = array 
;			[ebp + 16] = hi      (the lower limit of random number values)
;           [ebp + 20] = lo      (upper limit of random number values)
;
; Returns: "array" is filled with random numbers
;---------------------------------------------------------------------------------------------------------------
FillArray PROC
	PUSH ebp               	
	MOV ebp, esp
	PUSHAD                  ;Save registers
	
	MOV edi, [ebp+12]       ;Store array in edi
	MOV ecx, [ebp+8]        ;Set the loop counter equal to request

	MOV edx, [ebp + 20]               
	SUB edx, [ebp + 16]   
	INC edx                 ;Set edx equal to hi - lo + 1 (the range of random number values)
	CLD                     ;Clear the direction flag
	
addElement:
	MOV eax, edx            
	CALL RandomRange        ;Generate a random number in the range [0, hi - lo]
	ADD eax, [ebp + 16]     ;Add lo to the random integer to adjust the range to [lo, hi]
	STOSD                   ;Store the random value in array
	LOOP addElement         ;Add the next random number to array
	
	POPAD                   ;Restore registers
	POP ebp
	RET 16
FillArray ENDP

;---------------------------------------------------------------------------------------------------------------
;                                                  DisplayList
;
; Displays the contents of array, with 10 values per line and three blank spaces between each value. ebx will 
; keep track of the number of values on a given line. A title will also be displayed indicating if the displayed
; values are sorted or unsorted
;
; Recieves: [ebp + 8]  = request (the user's desired number of random integers)
;           [ebp + 12] = array 
;			[ebp + 16] = the title of the displayed list (sorted or unsorted)
;           [ebp + 20] = blank space to add between values
;
; Returns: N/A
;---------------------------------------------------------------------------------------------------------------
DisplayList PROC
	PUSH ebp
	MOV ebp, esp
	PUSHAD               ;Save registers
	
	MOV esi, [ebp+12]    ;Store the array in esi
	MOV ecx, [ebp+8]     ;Set the loop counter equal to request
	MOV ebx, 0           ;Clear the ebx register
	CLD                  ;Clear the direction flag
	
	CALL Crlf
	MOV edx, [ebp + 16]  
	CALL WriteString     ;Display the list title
	
displayElement:
	LODSD
	CALL WriteDec        ;Display array element
	INC ebx              ;Increment the number of values on the current line
	MOV edx, [ebp+20]    
	CALL WriteString     ;Add three blank spaces 
	CMP ebx, 10          
	JNE sameLine         ;If there are 10 values on the current line, start a new line and reset ebx
	CALL Crlf
	MOV ebx, 0
sameLine:
	LOOP displayElement  ;Move on to the next element in the array
	CALL Crlf
	
	POPAD                ;Restore registers
	POP ebp
	RET 16
DisplayList ENDP

;---------------------------------------------------------------------------------------------------------------
;                                                  DisplayMedian
;
; Displays the median value of the sorted list. If the list has an odd number of elements, the median value is
; simply the middle value. However if the list has an even number of elements, the median is the average of the 
; two middle values. Rounding occurs where necessary. 
;
; Recieves: [ebp + 8]  = request (the user's desired number of random integers)
;           [ebp + 12] = array 
;			[ebp + 16] = the median value string
;
; Returns: N/A
;---------------------------------------------------------------------------------------------------------------
DisplayMedian PROC
	PUSH ebp
	MOV ebp, esp
	PUSHAD                     ;Save registers
	
	MOV esi, [ebp + 12]        ;Set the array to esi
	MOV eax, [ebp + 8]         ;Set eax equal to request
	
	MOV edx, 0                 ;Clear the edx register in preparation for the DIV instruction
	MOV ebx, 2
	DIV ebx                    ;Divide request by two to determine if it is even or odd
	
	CMP edx, 0                 
	JE evenElements            ;If there is no remainder, jump to the evenElements section
	
	MOV ebx, eax               ;eax equals the index of the middle element in an odd list
	MOV eax, [esi + ebx*4]     ;Set eax equal to the value of the middle element (which is the median value)
	JMP display                ;Jump to the display section

evenElements:
	MOV ebx, eax               ;Set ebx equal to the index of the first middle value
	MOV ecx, eax
	DEC ecx                    ;Set ecx equal to the index of the second middle value
	MOV eax, 0                 ;Clear eax
	ADD eax, [esi + ebx*4]
	ADD eax, [esi + ecx*4]     ;eax now equals the sum of the middle two elements
	
	MOV edx, 0
	MOV edi, 2
	DIV edi                    ;Divide eax by two to get the average of the middle two elements
	
	CMP edx, 1               
	JE roundUp                 ;If there was a remainder, jump to the roundUp section
	JMP display                ;If there was no remainder, eax equals the median value. Jump to display
	
roundUp:
	INC eax                    ;Round up by incrementing eax. eax now holds the median value
	
display:
	CALL Crlf
	MOV edx, [ebp + 16]
	CALL WriteString           ;Display the median string
	CALL WriteDec              ;Display the median value
	CALL Crlf

	POPAD                      ;Restore registers
	POP ebp
	RET 12
DisplayMedian ENDP

;---------------------------------------------------------------------------------------------------------------
;                                                  SortList

; Sorts the contents of an array using the following selection sort algorithm where EAX = i, EBX = k, EDX = j
;
; for(k=0; k<request-1; k++) {  
;     i = k;  
;     for(j=k+1; j<request; j++) {   
;          if(array[j] > array[i])    
;          i = j;  
;     }  
;     exchange(array[k], array[i]); 
; }
;
; A sub-procedure, ExchangeElements, is called to perform the exchange command shown above.
;
; Recieves: [ebp + 8]  = request (the user's desired number of random integers)
;           [ebp + 12] = array 
;
; Returns: Sorted values in array
;---------------------------------------------------------------------------------------------------------------
SortList PROC
	PUSH ebp
	MOV ebp, esp
	PUSHAD              	;Save registers
	
	MOV esi, [ebp+12]       ;Set the array to esi
	MOV ecx, [ebp+8]        
	DEC ecx                 ;Set the outer loop counter equal to request-1
	MOV ebx, 0              ;Initialize k to 0
		
L1:                         ;The outer loop of the selection sort algorithm
	MOV eax, ebx            ;Set i = k
	MOV edx, ebx            
	ADD edx, 4              ;Set j = k + 1 
	PUSH ecx                ;Store the current count on the stack
	MOV ecx, [ebp+8]        ;Set the new count equal to request
	
L2:                         ;The inner loop of the selection sort algorithm
	MOV edi, [esi + edx]    ;Move array[j] to edi
	CMP edi, [esi + eax]    ;Compare array[j] to array[i]
	JLE IncrementJ          ;If array[j] > array [i], set i equal to j
	MOV eax, edx

IncrementJ:
	ADD edx, 4              ;Increment j 
	LOOP L2                 ;Continue with the inner loop

	PUSH ebx                ;Pass k to ExchangeElements
	PUSH eax                ;Pass i to ExchangeElements
	PUSH [ebp + 12]         ;Pass the array to ExchangeElements
	CALL ExchangeElements   ;Swap array[k] and array [i]
	
	POP ecx                 ;Restore the loop counter for the outer loop
	ADD ebx, 4              ;Increment k
	LOOP L1                 ;Continue with the outer loop

	POPAD                   ;Restore registers
	POP ebp
	RET 8
SortList ENDP

;---------------------------------------------------------------------------------------------------------------
;                                                  ExchangeElements
;
; Swaps the values of two elements, array[i] and array[k], in an array.
;
; Recieves: [ebp + 8]  = array 
;           [ebp + 12] = index i
;           [ebp + 16] = index k
;
; Returns: Swapped contents of array[i] and array[k]
;---------------------------------------------------------------------------------------------------------------
ExchangeElements PROC
	PUSH ebp
	MOV ebp, esp
	PUSHAD                 ;Save registers
	
	MOV esi, [ebp + 8]     ;Move the array to esi
	MOV eax, [ebp + 12]    ;Move i to eax
	MOV ebx, [ebp + 16]    ;Move k to ebx 
	MOV edx, [esi + ebx]   ;Store array[k] in edx
	MOV edi, [esi + eax]   ;Store array[i] in edi
	MOV [esi + ebx], edi   ;Swap Elements
	MOV [esi + eax], edx
	
	POPAD                  ;Restore registers
	POP ebp
	RET 12
ExchangeElements ENDP

END main