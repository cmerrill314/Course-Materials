; Christopher Merrill
; merrillc@oregonstate.edu
; CS271-400
; Program #3
; Due 2/12/2017

;---------------------------------------------------------------------------------------------------------------
;                                      NEGATIVE INTEGER ACCUMULATOR
;
; This program takes a series of negative integers (from -100 to -1) as input and returns the sum and rounded
; average of those integers. As the user enters values, they are added to the sum and the count is increased.
; The sum and count can then be used to determine the average, at which point a series of additional steps 
; determine if the average should be rounded up or down. 
;---------------------------------------------------------------------------------------------------------------

INCLUDE Irvine32.inc

.data
sum SDWORD 0              ;contains the sum of the user-entered values
count SDWORD 0            ;the number of valid entries
average SDWORD 0          ;contains the average of the user-entered values
remainder SDWORD ?        ;used for rounding purposes
lowerLimit SDWORD -100    ;lower limit of valid entries 
buffer BYTE 21 DUP(0)     ;buffer used for name entry

;Text Fragments:
header BYTE "Programming Assignment #3: Integer Accumulator",0dh,0ah,0
author BYTE "by Christopher Merrill",0dh,0ah,0
extraCredit BYTE "**EC: NUMBERED THE LINES DURING USER INPUT",0dh,0ah,0
instruction1 BYTE "Enter your name: ",0
instruction2 BYTE "Continue to enter integers in the range [-100, -1].",0dh,0ah,0
instruction3 BYTE "Enter any non-negative integer when you are finished.",0dh,0ah,0 
instruction4 BYTE ". Enter an integer: ",0
greeting BYTE "Nice to meet you ",0
invalid BYTE "Oops, make sure you enter an integer value that is between -100 and -1.",0dh,0ah,0 
resultsText BYTE "***RESULTS***",0dh,0ah,0
noEntryText BYTE "You didn't enter any valid integers, so the sum and average couldn't be calculated...",0
numbersEntered BYTE "Valid integer entries: ",0
sumResult BYTE "Sum of valid entries: ",0
averageResult BYTE "Rounded average of valid entries: ",0
remainderResult BYTE "Remainder amount: ",0
goodbye BYTE "Farewell ",0

.code
main PROC
;---------------------------------------------------------------------------------------------------------------
; The introduction section displays the program and author names. It also asks the user for their name and 
; displays the greeting. The user's name is then stored in the stack for use at the end of the program. 
;---------------------------------------------------------------------------------------------------------------
introduction:	
	;Display Header Using WriteString
	MOV	edx, OFFSET header
	CALL WriteString
	MOV	edx, OFFSET author
	CALL WriteString
	CALL Crlf
	MOV edx, OFFSET extraCredit
	CALL WriteString
	CALL Crlf
	
	;Get User's Name Using ReadString
	MOV	edx, OFFSET instruction1
	CALL WriteString
	MOV edx, OFFSET buffer
	MOV ecx, SIZEOF buffer
	CALL ReadString
	
	;Greet User
	PUSH edx                 ;push the name to the stack for later use
	MOV edx, OFFSET greeting ;display the greeting
	CALL WriteString
	POP edx                  ;pop the name and display it
	CALL WriteString
	PUSH edx                 ;push the name back to the stack
	CALL Crlf
	Call Crlf
	
;---------------------------------------------------------------------------------------------------------------
; The userInstructions section provides the user with the necessary information for running the program.
;---------------------------------------------------------------------------------------------------------------		
userInstructions:
	;Display Instructions
	MOV edx, OFFSET instruction2
	CALL WriteString
	MOV edx, OFFSET instruction3
	CALL WriteString
	CALL Crlf

;---------------------------------------------------------------------------------------------------------------
; The accumulator section is a loop that takes in values from the user, validates them, and adds them to the 
; sum. Each time a valid integer is added to the sum, the count is incremented. 
;---------------------------------------------------------------------------------------------------------------	
accumulator:
	;EXTRA CREDIT: Number the lines by displaying the count + 1. 
	MOV eax, count
	ADD eax, 1
	CALL WriteDec
	
	;Display instruction4
	MOV edx, OFFSET instruction4
	CALL WriteString
	
	;Get the signed value
	CALL ReadInt
	JO invalidEntry ;jump if the overflow flag is set (indicates non-integer input)
	
	;Validate input
positiveCheck:
	;If the entered value is a positive integer, jump to the results section
	MOV edx, -1
	CMP edx, eax
	JL results
	
validCheck:
	;Assure the entered value is less than or equal to -1
	MOV edx, -1
	CMP edx, eax
	JGE validCheck2 ;if the entry was less than 0, move on to valid check two
	
invalidEntry:
	;If the entry was invalid, jump back to accumulator to allow for another try
	MOV edx, OFFSET invalid
	CALL WriteString
	JMP accumulator
	
validCheck2:
	;Assure that the entered value is greater than or equal to -100
	CMP eax, lowerLimit
	JL invalidEntry
	
update:
	;Add the entry to sum
	ADD sum, eax
	;Increment the count
	INC count
	;Jump back to accumulator to accept another entry
	JMP accumulator

;---------------------------------------------------------------------------------------------------------------
; The results section calculates and displays the number of valid integer entries, the sum of the entries, and 
; the rounded average of the entries. If no valid entries were made, a message is displayed rather than the sum
; or average. 
;---------------------------------------------------------------------------------------------------------------	
results:
	;Display results header
	CALL Crlf
	MOV edx, OFFSET resultsText
	CALL WriteString

	;Display the number of valid integers entered
	MOV edx,OFFSET numbersEntered
	CALL WriteString
	MOV eax, count
	CALL WriteDec
	CALL Crlf
	
	;If the count is zero, skip the sum and average
	MOV edx, 0
	CMP edx, count
	JE noEntries
	
	;Display the sum
	MOV edx, OFFSET sumResult
	CALL WriteString
	MOV eax, sum
	CALL WriteInt
	CALL Crlf
	
	;Calculate average using signed-integer division (IDIV)
	MOV edx, 0
	CDQ          ;sign extend the eax value into edx:eax before using IDIV
	IDIV count
	
	;Store division results
	MOV average, eax
	MOV remainder, edx
	
	;Determine whether or not the average should be rounded up or down
	MOV eax, remainder
	SUB eax, remainder
	SUB eax, remainder
	SUB eax, remainder  ;eax now holds the absolute value of twice the remainder
	CMP eax, count 
	JG roundDown        ;if the absolute value of twice the remainder is greater than the number of terms (count),
	                    ;then the average needs to be rounded down (jump to round down). Otherwise display the 
						;average as-is. 
	JMP displayAverage
	
roundDown:
	;Round down if necessary
	DEC average
	
displayAverage:
	;Display the average value
	MOV edx, OFFSET averageResult
	CALL WriteString	
	MOV eax, average
	CALL WriteInt
	JMP farewell ;jump to farewell message
	
noEntries:
	MOV edx, OFFSET noEntryText
	CALL WriteString
	
;---------------------------------------------------------------------------------------------------------------
; The farewell section displays the farewell message. It retrieves the users name from the stack using POP. 
;---------------------------------------------------------------------------------------------------------------
farewell:
	;Display Farewell Message
	CALL Crlf
	CALL Crlf
	MOV edx, OFFSET goodbye
	CALL WriteString
	POP edx ;pop name back from the stack to display
	CALL WriteString
	CALL Crlf
	CALL Crlf

;Exit Program
exit
	
main ENDP
END main