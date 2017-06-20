; Christopher Merrill
; merrillc@oregonstate.edu
; CS271-400
; Program #3
; Due 2/19/2017

;---------------------------------------------------------------------------------------------------------------
;                                             COMPOSITE NUMBERS
;
; This program provides the user with a list of composite numbers. The user specifies the number of composite 
; numbers they would like to see, in the range 1 - 400. The ShowComposites procedure loops through each positve
; integer and checks to see if it is composite. To check if a value is composite, it is divided by all integers
; lower than itself to check for factors (if the number of factors is greater than two, we know the value is
; composite). 
;---------------------------------------------------------------------------------------------------------------

INCLUDE Irvine32.inc

.data
upperLimit DWORD 400 ;The upper limit of valid user entries
n          DWORD ?   ;The user-specified number of composite integers to display
number     DWORD ?   ;The current number in the ShowComposites loop
value      DWORD ?   ;USED IN CHECKING IF A NUMBER IS COMPOSITE. This is the value that is being checked
testValue  DWORD ?   ;USED IN CHECKING IF A NUMBER IS COMPOSITE. This value is evaluated as a potential factor of "value"
factors    DWORD ?   ;USED IN CHECKING IF A NUMBER IS COMPOSITE. Keeps track of the number of factors "value" has
count      DWORD 0   ;The number of terms that have been printed on the current line

;Text Fragments:
header       BYTE "Programming Assignment #4: Composite Numbers",0dh,0ah,0
author       BYTE "by Christopher Merrill",0dh,0ah,0
extraCredit  BYTE "**EC: Output columns are aligned",0dh,0ah,0
instruction1 BYTE "How many composite integers would you like to see?",0dh,0ah,0
instruction2 BYTE "Please stick to the range [1, 400]",0dh,0ah,0 
instruction3 BYTE "Enter a value: ",0
invalid      BYTE "Oops, make sure you enter an integer value that is between 1 and 400...",0dh,0ah,0 
goodbye      BYTE "Farewell!",0dh,0ah,0
fiveSpaces   BYTE "     ",0
fourSpaces   BYTE "    ",0
threeSpaces  BYTE "   ",0

.code
main PROC

CALL Introduction     ;Display the introduction 
CALL GetData          ;Retrieve a valid integer from the user
CALL ShowComposites   ;Dispay the desired number of composite numbers
CALL Farewell         ;Display the farewell message
exit                  ;Exit Program
	
main ENDP
;---------------------------------------------------------------------------------------------------------------
;                                               Introduction
;
; Displays the program title, programmer name, extra credit statement and initial user instructions. 
;
; Recieves: N/A
; Returns: N/A 
;---------------------------------------------------------------------------------------------------------------
Introduction PROC
	;Display program title
	MOV edx, OFFSET header
	CALL WriteString
	
	;Display programmer's name
	MOV	edx, OFFSET author
	CALL WriteString
	CALL Crlf
	
	;Display extra credit info
	MOV	edx, OFFSET extraCredit
	CALL WriteString
	CALL Crlf
	
	;Display initial instructions
	MOV	edx, OFFSET instruction1
	CALL WriteString
	MOV	edx, OFFSET instruction2
	CALL WriteString
	CALL Crlf
	
	;Return to main
	ret
Introduction ENDP

;---------------------------------------------------------------------------------------------------------------
;                                                   GetData
;
; Gets a valid integer from the user, in the range [1, 400]. Utlizes the Validate procedure for input validation.
; Continues to ask the user to input a value until a valid integer is entered. 
;
; Recieves: N/A
; Returns: EAX = validated number of composite numbers to display 
;---------------------------------------------------------------------------------------------------------------
GetData PROC

readInput:
	;Ask the user to enter an integer
	MOV edx, OFFSET instruction3
	CALL WriteString
	CALL ReadDec
	
	;Validate the user's input using the Validate procedure
	CALL Validate
	
	;Check the results of Validate
	CMP eax, 0
	JE readInput ;Jump back to the top if the results are invalid
	
	;Set n equal to the validated integer
	MOV n, eax

	;Return to main
	ret
GetData ENDP

;---------------------------------------------------------------------------------------------------------------
;                                                  Validate
;
; Recieves an integer to validate from the GetData procedure. Checks to make sure the value is an integer between
; 1 and 400. If it is, the value is sent back to getData in EAX. If it isn't, 0 is returned in EAX and a message
; is displayed to the user to try again.
; 
; Recieves: EAX = number to be validated
; Returns: EAX = validated number (if the number was valid)
;              = 0                (if the number was invalid)
;---------------------------------------------------------------------------------------------------------------
Validate PROC
	;First check the overflow flag to determine if the value is an integer
	JO invalidEntry
	
	;Next check if the value is greater than 0
	MOV edx, 0
	CMP eax, edx
	JLE invalidEntry
	
	;Fianally, check that the value is less than or equal to the upper limit
	MOV edx, upperLimit
	CMP eax, edx
	JLE return
	
invalidEntry:
	MOV eax, 0  ;set eax to zero for an invalid entry
	MOV edx, OFFSET invalid
	CALL WriteString
	
return:
	;Return to GetData
	ret
Validate ENDP

;---------------------------------------------------------------------------------------------------------------
;                                                ShowComposites
;
; Displays the user-specified number of composite numbers. Loops through each positive integer, starting at zero,
; and uses the IsComposite procedure to determine if that integer should be displayed or not. Once the number of
; displayed integers equals the user-specified value n, the loop exits and the procedure returns back to main.
; 
; Recieves: EAX = number of composite integers to show
; Returns: N/A
;---------------------------------------------------------------------------------------------------------------
ShowComposites PROC
	CALL Crlf
	MOV number, 1	;Initialize number to 1
	MOV ecx, n      ;Set the loop counter equal to the user-specified number of integers to display
	
display:
	;Set eax to number to be passed to the IsComposite procedure
	MOV eax, number
	
	;Check if the current number is a composite number
	PUSH ecx         ;Store the current ecx value
	CALL IsComposite ;Run the IsComposite procedure with the current number
	POP ecx          ;Restore ecx
	CMP eax, 0
	JE notComposite
	
	;Display the composite number
	MOV eax, number
	CALL WriteDec
	INC count
	
	;Check if a new line should be made and adjust spacing if necessary
	CMP count, 10
	JNE spacing
	CALL Crlf     ;Create a new line
	MOV count, 0  ;Reset count
	
increment:
	;Increment number to check the next positive integer
	INC number            
	LOOP display
	
notComposite:
	INC number ;Move on to the next positive integer
	INC ecx   ;The loop counter should only decrease for a composite number
	LOOP display
	
	;Return to main
	ret

;EXTRA CREDIT: COLUMN ALIGNMENT
;The number of spaces printed to the screen depends on the number of digits the current value has. 
spacing:
    ;If the number has one digit, print 5 spaces
	CMP eax, 9
	JG doubleDigits
	MOV edx, OFFSET fiveSpaces
	CALL WriteString
	JMP increment
	
doubleDigits:
	;If the number has 2 digits, print 4 spaces
	CMP eax, 99
	JG tripleDigits
	MOV edx, OFFSET fourSpaces
	CALL WriteString
	JMP increment
	
tripleDigits:
	;If the number has 3 digits, print 3 spaces
	MOV edx, OFFSET threeSpaces
	CALL WriteString
	JMP increment
	
ShowComposites ENDP

;---------------------------------------------------------------------------------------------------------------
;                                             IsComposite
;
; Determines if a given value is composite or prime by counting the number of factors that value has. The number
; of factors is determined by examining the remainder of the the DIV instruction for all positive integers that 
; are smaller than the given value. The result is then returned in eax as a boolean value (1=composite, 0=prime)
; 
; Recieves: EAX = integer to evaluate
; Returns: EAX = 1   (for a composite result)
;              = 0   (for a prime result)
;---------------------------------------------------------------------------------------------------------------
IsComposite PROC
	;Initializations
	MOV value, eax   ;Initialize value to the integer that is to be evaluated
	MOV testValue, 1 ;Initialize testValue to 1
	MOV factors, 0   ;Initialize the number of factors to 0
	MOV ecx, value   ;Set the loop counter equal to the value to be examined
	
findFactors:
	;Divide the value by the test value
	MOV eax, value
	MOV edx, 0
	DIV testValue
	;If there is no remainder, then a factor was found and factors is intremented
	CMP edx, 0
	JNE incrementTestValue
	INC factors
	
incrementTestValue:
	;Move on to the next test value to check for more factors
	INC testValue
	LOOP findFactors
	
	;Determine if the integer was composite by checking the number of factors
	CMP factors, 2
	JG composite
	;If value is prime, return 0 in eax
	MOV eax, 0
	;Return to ShowComposites
	ret
	
composite:
	;If value is composite, return 1 in eax
	MOV eax, 1
	;Return to ShowComposites
	ret
IsComposite ENDP
;---------------------------------------------------------------------------------------------------------------
;                                      Farewell
;
; Displays a farewell message to the user.
;
; Recieves: N/A
; Returns: N/A 
;---------------------------------------------------------------------------------------------------------------
Farewell PROC
	;Display farewell message
	CALL Crlf
	CALL Crlf
	MOV	edx, OFFSET goodbye
	CALL WriteString
	CALL Crlf

	;Return to main
	ret
Farewell ENDP

END main