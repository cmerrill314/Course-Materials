; Christopher Merrill
; merrillc@oregonstate.edu
; CS271-400
; Program #2
; Due 1/29/17

;---------------------------------------------------------------------------------------------------------------
; This program displays a user-specified number of terms from the Fibonacci Sequence. The user first enters their
; name and is greeted. The user then enters the number of terms they would like to see and the terms are displayed
; in rows of 5. The program then displays a farwell message before exitting.
;---------------------------------------------------------------------------------------------------------------
INCLUDE Irvine32.inc

.data
numTerms DWORD ?      ;the user-specified number of terms to display
buffer BYTE 21 DUP(0) ;buffer used for name entry
upperLimit DWORD 47   ;upper limit for number of term entry
count DWORD 2         ;used to decide when to skip to a new line in the display
prevTerm DWORD 1      ;the previous term in the Fibonacci Sequence
prevPrevTerm DWORD 0  ;the term before the previous term in the Fibonacci Sequence

;Text Fragments
header BYTE "Programming Assignment #2: Fibonacci Sequence",0dh,0ah,0
author BYTE "by Christopher Merrill",0dh,0ah,0
inst1 BYTE "Enter your name: ",0
greet BYTE "A pleasure to meet you ",0
inst2 BYTE "How many Fibonnaci terms you would like to display?",0dh,0ah,0
inst3 BYTE "Enter an integer from 1 to 46: ",0
invalid BYTE "Invalid entry...",0
goodbye BYTE "Thanks for playing ",0
space BYTE "     ",0

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
	
	;Get User's Name Using ReadString
	MOV	edx, OFFSET inst1
	CALL WriteString
	MOV edx, OFFSET buffer
	MOV ecx, SIZEOF buffer
	CALL ReadString
	
	;Greet User
	PUSH edx              ;push the name to the stack for later use
	MOV edx, OFFSET greet ;display the greeting
	CALL WriteString
	POP edx               ;pop the name and display it
	CALL WriteString
	PUSH edx              ;push the name back to the stack
	CALL Crlf
	Call Crlf

;---------------------------------------------------------------------------------------------------------------
; The userInstruction asks the user to enter the number of terms they would like to see.
;---------------------------------------------------------------------------------------------------------------	
userInstructions:
	;Display Instructions
	MOV edx, OFFSET inst2
	CALL WriteString

;---------------------------------------------------------------------------------------------------------------
; The getUserData section first gets the number of terms from the user. It then checks to assure that the entered
; value is an integer between 1 and 46 by doing the following: In validCheck the number of terms is set and 
; compared against 0. If the term is greater than zero the program jumps to validCheck2, otherwise it runs 
; invalidEntry and loops back to the top of getUserData. validCheck2 checks that the value is less than 47 using
; the same method as validCheck. Once a valid integer is entered, the program moves onto validEntry
;---------------------------------------------------------------------------------------------------------------
getUserData:
	MOV edx, OFFSET inst3
	CALL WriteString

	;Get Number Of Terms Using ReadDec
	CALL ReadDec
	
validCheck:	
	;Set Value
	MOV numTerms, eax 
	CALL Crlf
	
	;Assure Value Is Greater Than 0
	MOV edx, 0
	CMP edx, numTerms
	JL validCheck2    ;POST-TEST LOOP: if the number is greater than 0 jump to validCheck2
	
invalidEntry:
	MOV	edx, OFFSET invalid
	CALL WriteString
	JMP getUserData
	
validCheck2:
	;Assure Value Is Less Than 47
	MOV edx, upperLimit
	CMP edx, numTerms
	JG validEntry     ;POST-TEST LOOP: if the number is less than 47 jump to validEntry
	JMP invalidEntry  ;else run invalidAnswer

;---------------------------------------------------------------------------------------------------------------
; The validEntry section performs the necessary preparations before displaying the Fibonacci numbers. It sets 
; the counter ECX to one less than the number of terms entered by the user (because the first term, 1, is displayed
; before the loop begins), then displays the first value. If the user chose to see only one value, the next section
; is skipped and the program moves onto the farewell section. 
;---------------------------------------------------------------------------------------------------------------
validEntry:
	;Set Counter
	MOV ecx, numTerms
	DEC ecx
	
	;Display First Value
	MOV eax, 1
	CALL WriteDec
	MOV edx, OFFSET space
	CALL WriteString
	
	;If The Number Of Terms Is 1, Skip The displayFibs Loop Below
	CMP ecx, 0
	JE farewell

;---------------------------------------------------------------------------------------------------------------
; The displayFibs section displays the numbers in the Fibonacci sequence. The algorithm is outlined step by step
; in the comments below (most of the code deals with formatting the spacing and new lines). The "count" variable is
; only used to determine when to move on to the next line, it has nothing to do with calculating the Fibonacci
; number. 
;---------------------------------------------------------------------------------------------------------------
displayFibs:
    ;Display Value
	MOV eax, 0              ;reset EAX
	ADD eax, prevTerm       ;add the previous term to EAX
	ADD eax, prevPrevTerm   ;add the term before the previous term to EAX
	CALL WriteDec           ;display the new Fibonacci number
	MOV edx, OFFSET space   ;add 5 blank spaces
	CALL WriteString
	
	;Assure Only 5 Values Are Displayed Per Line
	CMP count, 5            ;if the count is not equal to 6, move onto the the second part
	JNE displayFibs2        ;otherwise move onto the next line and reset the count
	CALL Crlf
	MOV count, 0            ;reset count
	
displayFibs2:
	;Update prevTerm, prevPrevTerm And Count Before Restarting The Loop
	MOV ebx, prevTerm
	MOV prevPrevTerm, ebx
	MOV prevTerm, eax
	INC count
	LOOP displayFibs

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