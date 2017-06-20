; Christopher Merrill
; merrillc@oregonstate.edu
; CS271-400
; Program #6A
; Due 3/19/2017

;---------------------------------------------------------------------------------------------------------------
;                                   PROGRAM 6A: LOW-LEVEL I/O PROCEDURES
;
; Uses a ReadVal procedure to read in 10 digit-strings from the user. Each digit-string is validated and 
; converted to an integer value, at which point it is stored in an array. Once 10 valid integers are entered, 
; the contents of the array are displayed using a WriteVal procedure. The WriteVal procedure coverts each integer
; in the array back into a string value before displaying it. After the array is displayed, the GetAverage 
; procedure calculates and displays both the sum and the average of the array contents. 
;
; The getString and displayString macros are used within the ReadVal and WriteVal procedures respectively. 
;---------------------------------------------------------------------------------------------------------------

INCLUDE Irvine32.inc

;---------------------------------------------------------------------------------------------------------------
getString MACRO prompt, buffer, buffSize
;
; Retrieves a string from the user using Irvine's ReadString procedure
;
; Recieves: prompt = the OFFSET of a string that instructs the user to enter a string
;           buffer = the OFFSET of an input buffer, which determines the max size of the entered value
;           buffSize = the size of the input buffer (decimal value)
;
; Returns: EDX = user-enterd string 
;          EAX = size of the user-entered string
;
; Avoid passing ECX, EDX or EAX as arguments.
;---------------------------------------------------------------------------------------------------------------
	PUSH ecx           ;Save ECX register on the stack
	MOV edx, prompt
	CALL WriteString   ;Prompt the user to enter a valid digit-string
	MOV edx, buffer    ;Store the input buffer in EDX
	MOV ecx, buffSize  ;Store the buffer size in ECX
	CALL ReadString    ;Read in the digit-string with ReadString
	POP ecx            ;Restore ECX register
ENDM

;---------------------------------------------------------------------------------------------------------------
displayString MACRO string
;
; Displays a string using Irvine's WriteString procedure
;
; Recieves: string = the OFFSET of the string that will be displayed
;
; Avoid passing EDX as an argument
;---------------------------------------------------------------------------------------------------------------
	PUSH edx            ;Save EDX register on the stack
	MOV edx, string
	CALL WriteString    ;Use WriteString to display the desired string
	POP edx             ;Restore EDX register
ENDM

.data
numDigits    DWORD 10          ;The number of digits that the user will enter
value        DWORD ?           ;Holds a user-entered value during string-to-int conversion
bufferSize   DWORD 21          ;The size of the input buffer (used in getString MACRO)
array        DWORD 40 DUP(?)   ;Holds the user-entered digits
stringArray  BYTE  11 DUP(?)   ;Holds a digit-string as it is being converted from an integer type to a string
inputBuffer  BYTE  21 DUP(0)   ;Input buffer used in getString Macro. 

;Strings:
header       BYTE "Programming Assignment 6A: Designing Low-Level I/O Procedures",0dh,0ah,0
author       BYTE "by Christopher Merrill",0dh,0ah,0
instruction1 BYTE "Enter 10 unsigned decimal integers to recieve their sum and average.",0dh,0ah,0
instruction2 BYTE "Enter a value: ",0
invalid      BYTE "Invalid entry, make sure you enter a positive integer value...",0dh,0ah,0
listTitle    BYTE "You entered the following numbers:",0dh,0ah,0
sumText      BYTE "SUM: ",0
averageText  BYTE "AVERAGE: ",0
bye          BYTE "Farewell!",0dh,0ah,0
comma        BYTE ", ",0

.code
main PROC
	
	PUSH OFFSET instruction1  ;Pass the first line of instructions to the Introduction procedure
	PUSH OFFSET author        ;Pass the author information to the Introduction procedure
	PUSH OFFSET header        ;Pass the header to the Introduction procedure
	CALL Introduction         ;Display the introduction 
	
	PUSH bufferSize           ;Pass the size of the input buffer to the ReadVal procedure
	PUSH OFFSET value         ;Pass value to the ReadVal procedure
	PUSH OFFSET invalid       ;Pass the invalid entry message to the ReadVal procedure
	PUSH OFFSET instruction2  ;Pass the second instruction to the ReadVal procedure
	PUSH OFFSET inputBuffer   ;Pass the input buffer to the ReadVal procedure
	PUSH OFFSET array         ;Pass the empty array to the ReadVal procedure
	PUSH numDigits            ;Pass the specified number of digits to the ReadVal procedure
	CALL ReadVal              ;Populate array with 10 positive integer values.
	
	PUSH OFFSET comma         ;Pass the comma string to the WriteVal procedure (used for spacing)
	PUSH OFFSET listTitle     ;Pass the list title to the WriteVal procedure
	PUSH OFFSET stringArray   ;Pass an empty string array to WriteVal, to hold the converted strings
	PUSH OFFSET array         ;Pass the array of integers to WriteVal, which will be converted to strings
	PUSH numDigits            ;Pass the number of integers in the array to WriteVal
	CALL WriteVal             ;Convert the array contents from int to strings and display them
	
	PUSH OFFSET averageText   ;Pass the average text to the GetAverage procedure
	PUSH OFFSET sumText       ;Pass the sum text to the GetAverage procedure
	PUSH OFFSET array         ;Pass the filled array to the GetAverage procedure
	PUSH numDigits            ;Pass the size of array to the GetAverage procedure
	CALL GetAverage           ;Calculate/Display the sum and average of the elements in the array
	
	PUSH OFFSET bye           ;Pass the farewell message to the Farewell procedure
	CALL Farewell             ;Display the farewell message
	
	exit                      ;Exit the program
	
main ENDP
;---------------------------------------------------------------------------------------------------------------
;                                               Introduction
;
; Displays the program title, programmer name and initial user instructions. 
;
; Recieves: [ebp + 8]  = program title
;           [ebp + 12] = author information
;			[ebp + 16] = instruction
;			
; Returns: N/A 
;---------------------------------------------------------------------------------------------------------------
Introduction PROC
	PUSH ebp               
	MOV ebp, esp
	PUSHAD                     ;Save registers

	displayString [ebp + 8]    ;Display program title       
	displayString [ebp + 12]   ;Display programmer's name         
	CALL Crlf
	displayString [ebp + 16]   ;Display the first instruction line     
	CALL Crlf
	
	POPAD                      ;Restore registers and return
	POP ebp
	RET 12
Introduction ENDP

;---------------------------------------------------------------------------------------------------------------
;                                               ReadVal
;
; Reads in 10 valid digit-strings from the user. If an invalid digit-string is entered, the user will be 
; prompted to try again. Each digit of the user-entered string will be converted from ASCII to an integer value,
; then evaluated to be sure that it is in the range 0-9. If the resulting integer is valid, it will be stored in 
; array.
;
; Recieves: [ebp + 8]  = numDigits (the number of digits the user will enter)
;           [ebp + 12] = array
;           [ebp + 16] = input buffer (used in the getString MACRO)
;           [ebp + 20] = instruction that informs the user to enter a value (used in getString MACRO)
;           [ebp + 24] = invalid entry message
;           [ebp + 28] = value
;           [ebp + 32] = the size of the input buffer (used in getString MACRO)
;			
; Returns:  array is populated with 10 valid, user-entered integers
;---------------------------------------------------------------------------------------------------------------
ReadVal PROC
	PUSH ebp               
	MOV ebp, esp
	PUSHAD                              ;Save registers
	
	MOV edi, [ebp + 12]                 ;Store array in edi
	MOV ecx, [ebp + 8]                  ;Set the loop counter equal to numDigits
	
addElement:
	;Retrieve a digit-string from the user using the getString macro:
	getString [ebp + 20], [ebp + 16], [ebp + 32] 
  
	PUSH ecx                            ;Store loop counter
	CMP eax, 10                         ;If more than 10 digits were entered, the entry is invalid
	JG invalidEntry                       
	
	MOV ecx, eax                        ;The inner loop counter equals the number of characters in the string
	MOV esi, edx                        ;Point at the first character in the digit-string

convertString:
	MOV ebx, [ebp + 28]                 ;Use the variable "value" to hold the integer value of the digit-string                   
	MOV eax, [ebx]                      
	MOV ebx, 10                         
	MUL ebx                             ;Multiply value by 10
	MOV ebx, [ebp + 28]
	MOV [ebx], eax                      ;Add the result of the multiplication to value
	MOV al, [esi]                       
	INC esi
	SUB al, 48                          ;Subtract 48 from ASCII value of the digit to determine its integer value
	
	CMP al, 0                           ;Assure that the digit is greater than 0
	JL invalidEntry
	CMP al, 9                           ;Assure that the digit is less than 9
	JG invalidEntry                     
  
	MOV ebx, [ebp + 28]                    
	ADD [ebx], al                       ;Add the integer to value
	LOOP convertString                  ;Loop to the next character in the digit string
	JMP store                            
 
invalidEntry:                           
	displayString [ebp + 24]            ;Display the invalid entry message
	POP ecx                             ;Restore outer loop counter
	INC ecx                             ;Increment ECX since no value was retrieved
	JMP nextEntry                       
	
store:	                                
	MOV eax, [ebx]
	STOSD                               ;Store the integer value in the array using STOSD
	POP ecx                             ;Restore outer loop counter
  
nextEntry:
	MOV al, 0                           ;Reset registers and variables
	MOV eax, 0
	MOV ebx, [ebp + 28]                 
	MOV [ebx], eax
	LOOP addElement                     ;Collect the next value if ECX > 0

	POPAD                               ;Restore registers and return
	POP ebp
	RET 28
ReadVal ENDP

;---------------------------------------------------------------------------------------------------------------
;                                               WriteVal
;
; Converts each value in an integer array into a string, then displays each string in list form. Each value
; from the integer array is separated into digits by dividing it by 10, and then pushed to the stack (so that they
; can be added to the string array in reversed order). As each digit is popped, it is summed with 48 to determine
; its ASCII value before adding it to the string. Once a value from the integer array is successfully converted
; to a string, it is displayed and the process repeats for each remaining value in the array. The value "numDigits"
; will determine the number of times the loop repeats. 
;
; Recieves: [ebp + 8]  = numDigits (the number of values the user will enter)
;           [ebp + 12] = array
;           [ebp + 16] = string array
;           [ebp + 20] = list title
;           [ebp + 24] = comma (for spacing between values in the list)
;          
; Returns:  Displays the contents of array as string values
;---------------------------------------------------------------------------------------------------------------
WriteVal PROC
	PUSH ebp               
	MOV ebp, esp
	PUSHAD                       ;Save registers
	
	CALL Crlf
	displayString [ebp + 20]     ;Display the list title
	MOV esi, [ebp + 12]          ;Store array in esi
	MOV edi, [ebp + 16]          ;Store the string array in edi
	MOV ecx, [ebp + 8]           ;Set the loop counter equal to numDigits
	MOV ebx, 1                   ;Initialize ebx to 1, as a counter of the number of digits in a string
	CLD                          ;Clear the direction flag

displayStringValue:
	MOV edi, [ebp + 16]          ;Store the string array in edi
	LODSD                        ;Pull an integer value from ESI into EAX
	
convertInt:
	PUSH ebx                     ;Store the digit count
	MOV ebx, 10                  ;Set EBX to 10 as the upcoming divisor
	MOV edx, 0                   ;Clear EDX in preparation for division
	DIV ebx                      ;Divide EAX by 10 to isolate the last digit in the remainder
	POP ebx                      ;Restore the digit count after division is complete
	PUSH edx                     ;Store the last digit in the unsigned int on the stack
	CMP eax, 0            
	JE storeCount                ;If the quotient is 0, there are no more digits in the value
	INC ebx                      ;If the quotient is nonzero, collect the remaining digits and store them on the stack
	JMP convertInt           
	
storeCount:
	MOV edx, ecx                 ;Store the current count in edx (can't use stack as its already in use)
	MOV ecx, ebx                 ;Set the inner loop count equal to the number of digits in the current value
	
buildString:
	POP eax                      ;Pop a digit from the stack
	ADD al, 48                   ;Add 48 to get its ASCII value    
	STOSB                        ;Store the ASCII value in the string array
	LOOP buildString             ;Continue the loop for the remaining digits
	
	MOV al, 0                   
	STOSB                        ;Add a NULL terminator at the end of the string
	displayString [ebp + 16]     ;Display the string value
	MOV ecx, edx                 ;Move count back to ecx
	CMP ecx, 1                   ;Check to see if this is the last value in the list
	JE nextValue
	MOV ebx, 1                   ;If this isn't the last value, reset the digit count and display a comma for spacing
	displayString [ebp + 24]     
   
nextValue:                       
	LOOP displayStringValue      ;Move on to the next list value
	CALL Crlf                    
	CALL Crlf                    
	
	POPAD                        ;Restore registers and return
	POP ebp
	RET 20
WriteVal ENDP

;---------------------------------------------------------------------------------------------------------------
;                                               GetAverage
; 
; Calculates and displays the sum and average of the elements in a passed array. Elements are brought into the 
; EAX register one at a time (using LODSD) before adding them to EBX. After looping through all array elements, 
; EBX then holds the sum of all array elements. The sum is first displayed, then divided by the number of elements
; in the array to calculate the average. Finally, the average is then displayed. 
;
; Recieves: [ebp + 8]  = numDigits (the number of digits the user will enter)
;           [ebp + 12] = array
;           [ebp + 16] = sum text
;           [ebp + 20] = average text
;			
; Returns:  Displays the sum and average of the elements in the passed array
;---------------------------------------------------------------------------------------------------------------
GetAverage PROC
	PUSH ebp               
	MOV ebp, esp
	PUSHAD                     ;Save registers
	
	MOV esi, [ebp+12]          ;Store the array in esi
	MOV ecx, [ebp+8]           ;Set the loop counter equal to numDigits
	MOV ebx, 0                 ;Clear ebx so it can be used to hold the sum of the array values
	
sum:
	LODSD                      ;Load an array value
	ADD ebx, eax               ;Add the array value to ebx
	LOOP sum                   ;Move to the next array value
	
	displayString [ebp + 16]   ;Display the sum text   
	MOV eax, ebx
	CALL WriteDec              ;Display the sum (held in ebx)
	CALL Crlf

	MOV edx, 0                 ;Clear edx in preparation for DIV instruction
	MOV ebx, [ebp + 8]   
	DIV ebx                    ;Divide the sum (eax) by the number of digits (ebx) to get the average
	
	displayString [ebp + 20]   ;Display the average text    
	CALL WriteDec              ;Display the average (held in eax after the division)
	CALL Crlf
	CALL Crlf
	
	POPAD                      ;Restore registers and return
	POP ebp
	RET 16
GetAverage ENDP

;---------------------------------------------------------------------------------------------------------------
;                                               Farewell
;
; Displays the farwell message.
;
; Recieves: [ebp + 8]  = farewell message
;			
; Returns: N/A 
;---------------------------------------------------------------------------------------------------------------
Farewell PROC
	PUSH ebp               
	MOV ebp, esp
	PUSHAD                      ;Save registers

	displayString [ebp + 8]     ;Display farewell message     
	CALL Crlf
	
	POPAD                       ;Restore registers and return
	POP ebp
	RET 4
Farewell ENDP

END main