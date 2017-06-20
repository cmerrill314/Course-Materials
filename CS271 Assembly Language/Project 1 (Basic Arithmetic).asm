; Christopher Merrill
; merrillc@oregonstate.edu
; CS271-400
; Program #1
; Due 1/22/17

;---------------------------------------------------------------------------------------------------------------
; This program asks the user to enter 2 numbers. It then calculates the sum, difference, product, quotient
; and remainder of those numbers. In addition to the five subsections outlines in the assignment document 
; (introduction, get data, calculate required variables, display results, and say goodbye), this program also
; contains two additional subsections to handle the extra credit operations. These sections are "tryAgain" 
; and "badInput". Try again asks the user if they want to rerun or exit the program. badInput only runs if
; the second value entered by the user is greater than the first value.
;---------------------------------------------------------------------------------------------------------------
INCLUDE Irvine32.inc

.data
;Text Fragments
header BYTE "Programming Assignment #1: Basic Arithmetic",0dh,0ah,0
author BYTE "by Christopher Merrill",0dh,0ah,0
blankLine BYTE " ",0dh,0ah,0
instructions BYTE "Enter 2 Numbers To Find Out Their Sum, Difference, Product, Quotient, and Remainder.",0dh,0ah,0
firstText BYTE "First Number: ",0
secondText BYTE "Second Number: ",0
resultsText BYTE "***RESULTS***",0dh,0ah,0
sumText BYTE "Sum: ",0
differenceText BYTE "Difference: ",0
productText BYTE "Product: ",0
quotientText BYTE "Quotient: ",0
remainderText BYTE "Remainder: ",0
terminatingMessage BYTE "Thanks for playing, Bye!",0dh,0ah,0
tryAgainMessage BYTE "Would you like to try again? Enter 1 for Yes, 0 for No: " ,0
badInputMessage BYTE "Sorry, the first integer must be larger than the second integer...",0dh,0ah,0
extraCreditOne BYTE "**EC: Program verifies second number is less than first.",0dh,0ah,0
extraCreditTwo BYTE "**EC: Program repeats until user chooses to quit.",0dh,0ah,0

;User-Entered Numbers
numOne DWORD ?
numTwo DWORD ?

;Results
sum DWORD 0
difference DWORD 0
product DWORD ?
quotient DWORD ?
remainder DWORD ?

.code
main PROC
;---------------------------------------------------------------------------------------------------------------
; The intro section displays the program name, author, and extra-credit information. First each line of text is 
; moved into the EDX register, then it is called using WriteString. Blank lines are inserted to make the output
; easier to read. 
;---------------------------------------------------------------------------------------------------------------
intro:	
	;Display Header
	MOV	edx, OFFSET header
	CALL WriteString
	MOV	edx, OFFSET author
	CALL WriteString
	
	;Display Extra-Credit Indicator
	MOV	edx, OFFSET blankLine
	CALL WriteString
	MOV	edx, OFFSET extraCreditTwo
	CALL WriteString
	MOV	edx, OFFSET extraCreditOne
	CALL WriteString

;---------------------------------------------------------------------------------------------------------------
; The getData section prompts the user to enter 2 numbers. Text is displayed in the same way described above in 
; the intro section. The numbers are read into variables by calling ReadDec. At the end of this section, the 
; entered values are compared to assure that number two is less than number one. If that isn't the case, the 
; program jumps to the "badInput" section. 
;---------------------------------------------------------------------------------------------------------------
getData:
	;Display Instructions
	MOV	edx, OFFSET blankLine
	CALL WriteString
	MOV edx, OFFSET instructions
	CALL WriteString
	MOV	edx, OFFSET blankLine
	CALL WriteString
	
	;Input First Number
	MOV edx, OFFSET firstText
	CALL WriteString
	CALL ReadDec    ;read in value
	MOV numOne, eax ;store value
	
	;Input Second Number
	MOV edx, OFFSET secondText
	CALL WriteString
	CALL ReadDec    ;read in value
	MOV numTwo, eax ;store value
	MOV	edx, OFFSET blankLine
	CALL WriteString
	
	;Compare input (For Extra Credit)
	MOV eax, numOne
	CMP eax, numTwo
	JL badInput     ;jump to badInput section if number one is less than number two

;---------------------------------------------------------------------------------------------------------------
; The calculate section uses the ADD, SUB, MUL and DIV operations to calculate the sum, difference, product,
; quotient and remainder of the two entered integers. After each calculation, the results are stored in named
; variables.
;---------------------------------------------------------------------------------------------------------------
calculate:
	;Calculate Sum
	MOV eax, numOne
	ADD sum, eax     ;add the first number to sum
	MOV eax, numTwo
	ADD sum, eax     ;add the second number to sum
	
	;Calculate Difference
	MOV eax, numOne
	ADD difference, eax ;add the first number to difference
	MOV eax, numTwo
	SUB difference, eax ;carry out subtraction 
	
	;Calculate Product
	MOV eax, numOne
	MUL numTwo       ;carry out multiplication
	MOV product, eax ;move result to product variable
	
	;Calculate Quotient/Remainder
	MOV edx, 0         ;clear dividend
	MOV eax, numOne
	DIV numTwo         ;carry out division
	MOV quotient, eax  ;move quotient result to quotient variable
	MOV remainder, edx ;move remainder to remainder variable

;---------------------------------------------------------------------------------------------------------------
; The results section displays the values for the sum, difference, product, quotient and remainder of the two
; entered integers. It pulls the results that were previously stored in the calculate section. After displaying 
; the results, the sum and difference variables are reinitialized to zero in case the user decides to rerun the 
; program (the product/quotient/remainder variables don't need to be reset due to the way they are calculated). 
;---------------------------------------------------------------------------------------------------------------
results:
	;Display Results Text
	MOV edx, OFFSET resultsText
	CALL WriteString
	MOV	edx, OFFSET blankLine
	CALL WriteString
	
	;Display Sum
	MOV edx, OFFSET sumText
	CALL WriteString
	MOV eax, sum
	CALL WriteDec
	MOV	edx, OFFSET blankLine
	CALL WriteString
	
	;Display Difference
	MOV edx, OFFSET differenceText
	CALL WriteString
	MOV eax, difference
	CALL WriteDec
	MOV	edx, OFFSET blankLine
	CALL WriteString
	
	;Display Product
	MOV edx, OFFSET productText
	CALL WriteString
	MOV eax, product
	CALL WriteDec
	MOV	edx, OFFSET blankLine
	CALL WriteString
	
	;Display Quotient
	MOV edx, OFFSET quotientText
	CALL WriteString
	MOV eax, quotient
	CALL WriteDec
	MOV	edx, OFFSET blankLine
	CALL WriteString
	
	;Display Remainder
	MOV edx, OFFSET remainderText
	CALL WriteString
	MOV eax, remainder
	CALL WriteDec
	MOV	edx, OFFSET blankLine
	CALL WriteString
	MOV	edx, OFFSET blankLine
	CALL WriteString
	
	;Reset Result Values (in case the user decides to run the program again)
	MOV sum, 0
	MOV difference, 0
	MOV eax, 0

;---------------------------------------------------------------------------------------------------------------
; The tryAgain section prompts the user to enter 0 or 1. If the user enters 1, the program jumps back to the 
; getData section where two new numbers can be entered. If the user enters 0, the program runs the terminating
; message and exits. 
;---------------------------------------------------------------------------------------------------------------
tryAgain:
	;Ask User To Try Again
	MOV edx, OFFSET tryAgainMessage
	CALL WriteString
	CALL ReadDec
	CMP eax, 1   
	JE getData ;if the user entered 1, jump back to the getData section and rerun the program. else say goodbye

;---------------------------------------------------------------------------------------------------------------
; The goodbye section diplays a terminating message before exitting the program. 
;---------------------------------------------------------------------------------------------------------------	
goodbye:
	;Display Terminating Message
	MOV	edx, OFFSET blankLine
	CALL WriteString
	MOV	edx, OFFSET terminatingMessage
	CALL WriteString
	MOV	edx, OFFSET blankLine
	CALL WriteString

	;Exit Program
	exit

;---------------------------------------------------------------------------------------------------------------
; The badInput section notifies the user that their number entry was invalid (in the case that the second number
; entered was greater than the first). After notifying the user, the program automatically jumps to the try again 
; section. 
;---------------------------------------------------------------------------------------------------------------
badInput:
	;Notify User Of Invalid Number Entry
	MOV	edx, OFFSET badInputMessage
	CALL WriteString
	MOV	edx, OFFSET blankLine
	CALL WriteString
	JMP  tryAgain     ;jump to the try again section
	
main ENDP
END main