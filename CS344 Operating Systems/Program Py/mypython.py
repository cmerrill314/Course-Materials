#!/usr/bin/python
#-------------------------------------------------------------------------------------
# Christopher Merrill
# CS344
# Program Py
#
# This script does the following:
#   1. Generates three words consiting of 10 random lowercase letters, followed by a 
#      newline character.
#   2. Writes each random word to its own external file.
#   3. Generates 2 random integers and calculates their product.
#   4. Prints the 3 random words, 2 random integers and product to the console.
#-------------------------------------------------------------------------------------
import random #Used for random number/letter generation

#Random letters will be chosen from this string:
letters = 'abcdefghijklmnopqrstuvwxyz' 

#-------------------------------------------------------------------------------------
# generateRandomWord
#
# Generates a string of 10 random characters, followed by a newline character.
#-------------------------------------------------------------------------------------
def generateRandomWord():
	str = ''                              #Initialize a blank string           
	for num in range(0, 10):              #Loop 10 times
		letter = random.choice(letters)   #Choose a random lowercase letter
		str += letter                     #Append the new letter to str
	str += '\n'                           #Add a newline character
	return str                            #Return the random word

#Generate 3 random words	
word1 = generateRandomWord()
word2 = generateRandomWord()
word3 = generateRandomWord()

#Open 3 new files
file1 = open("file1.txt", "w")
file2 = open("file2.txt", "w")
file3 = open("file3.txt", "w")

#Write the random words into each file respectively
file1.write(word1)
file2.write(word2)
file3.write(word3)

#Generate two random integers between 1-42 
#NOTE: (1,43) is used because the second argument is exclusive rather than inclusive
int1 = random.randrange(1,43) 
int2 = random.randrange(1,43)

#Calculate the product of the two random integers
product = int1 * int2

#print the random words, integers and product
print (word1, end = '') 
print (word2, end = '')
print (word3, end = '')
print (int1)
print (int2)
print (product)