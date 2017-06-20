#include "Ant.hpp"

#include <iostream>
#include <string>
#include <unistd.h> //needed to pause the game between printing
using std::cout;
using std::endl;

//constructor definition
Ant::Ant(int rw, int col, int totRow, int totCol, int step)
{
	row = rw;
	column = col;
	totalSteps = step;
	totalRows = totRow;
	totalColumns = totCol;

	pauseTime = 12500;   //indicates the pause time between frames
	currentStep = 0;     //initialize the current step to 0.
	direction = "north"; //default starting direction is north
}

/*********************************************************************
**                        Ant::play
** This function contains all of the mechanics for Langton's Ant. It 
** first creates the game board and adds the ant. It then begins a 
** series of if/then statements that contain the game logic and repeat 
** until the correct number of steps have been executed. The two main 
** statements are "Is the current tile black, or white". Within each of
** those statements are four more statements that tell the ant what to
** do depending on which direction it is facing. 
*********************************************************************/
void Ant::play()
{
	std::string temp; //temporarily holds a tiles value
	
	//set the board size
	brd.setSizeRow(totalRows);
	brd.setSizeCol(totalColumns);
	//make the board
	brd.makeBoard();
	//add the ant to the board
	brd.setTileValue(row, column, "*");
	//clear the console to make way for the game board
	cout << "\033[2J\033[1;1H" << endl; 
	//print the board once in the beginning
	brd.print();
	//reset the ants to blank for the first step
	brd.setTileValue(row, column, "-");
	
	//main game loop, runs for the number of steps the user specified
	do
	{
		//if the tile the ant is currently standing on is blank
		if (brd.getTileValue(row, column) == "-")
		{
			//if the ant's current direction is north
			if (direction == "north")
			{
				//if the next move is on the map
				if ((column + 1) < brd.getSizeCol())
				{
					brd.setTileValue(row, column, "#");   //change the current tile's value to black
					direction = "east";                   //change the ant's direction
					column += 1;                          //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps       
				}
				//if the next move is off the map, perform a wrap around and have the ant come out of the left side of the board
				else
				{
					brd.setTileValue(row, column, "#");   //change the current tile's value to black
					direction = "east";                   //change the ant's direction
					column = 0;                           //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps 
				}	
			}
			//if the ant's current direction is east
			else if (direction == "east")
			{
				//if the next move is on the map
				if ((row + 1) < brd.getSizeRow())
				{
					brd.setTileValue(row, column, "#");   //change the current tile's value to black
					direction = "south";                  //change the ant's direction
					row += 1;                             //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps       
				}
				//if the next move is off the map, perform a wrap around and have the ant come out of the top of the board 
				else
				{
					brd.setTileValue(row, column, "#");   //change the current tile's value to black
					direction = "south";                  //change the ant's direction
					row = 0;                              //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps 
				}
			}
			//if the ant's direction is south
			else if (direction == "south")
			{
				//if the next move is on the map
				if ((column - 1) >= 0)
				{
					brd.setTileValue(row, column, "#");   //change the current tile's value to black
					direction = "west";                   //change the ant's direction
					column -= 1;                          //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps       
				}
				//if the next move is off the map, perform a wrap around and have the ant come out of the right side of the board 
				else
				{
					brd.setTileValue(row, column, "#");   //change the current tile's value to black
					direction = "west";                   //change the ant's direction
					column = totalColumns - 1;            //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps  
				}
			}
			//if the ant's direction is west
			else if (direction == "west")
			{
				//if the next move is on the map
				if ((row - 1) >= 0)
				{
					brd.setTileValue(row, column, "#");   //change the current tile's value to black
					direction = "north";                  //change the ant's direction
					row -= 1;                             //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board 
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps       
				}
				//if the next move is off the map, perform a wrap around and have the ant come out of the bottom of the board
				else
				{
					brd.setTileValue(row, column, "#");   //change the current tile's value to black
					direction = "north";                  //change the ant's direction
					row = totalRows - 1;                  //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board 
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps  
				}
			}
		}
		//if the tile the ant is currently standing on is "black"
		else
		{
			//if the ant's current direction is north
			if (direction == "north")
			{
				//if the next move is on the map
				if ((column - 1) >= 0)
				{
					brd.setTileValue(row, column, "-");   //change the current tile's value to black
					direction = "west";                   //change the ant's direction
					column -= 1;                          //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board 
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps       
				}
				//if the next move is off the map, perform a wrap around and have the ant come out of the right side of the board 
				else
				{
					brd.setTileValue(row, column, "-");   //change the current tile's value to black
					direction = "west";                   //change the ant's direction
					column = totalColumns - 1;            //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board 
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps 
				}
			}
			//if the ant's current direction is east
			else if (direction == "east")
			{
				//if the next move is on the map
				if ((row - 1) >= 0)
				{
					brd.setTileValue(row, column, "-");   //change the current tile's value to black
					direction = "north";                  //change the ant's direction
					row -= 1;                             //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps       
				}
				//if the next move is off the map, perform a wrap around and have the ant come out of the bottom of the board
				else
				{
					brd.setTileValue(row, column, "-");   //change the current tile's value to black
					direction = "north";                  //change the ant's direction
					row = totalRows - 1;                  //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps  
				}
			}
			//if the ant's direction is south
			else if (direction == "south")
			{
				//if the next move is on the map
				if ((column + 1) < brd.getSizeCol())
				{
					brd.setTileValue(row, column, "-");   //change the current tile's value to black
					direction = "east";                   //change the ant's direction
					column += 1;                          //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps       
				}
				//if the next move is off the map, perform a wrap around and have the ant come out of the left side of the board
				else
				{
					brd.setTileValue(row, column, "-");   //change the current tile's value to black
					direction = "east";                   //change the ant's direction
					column = 0;                           //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps 
				}
			}
			//if the ant's direction is west
			else if (direction == "west")
			{
				//if the next move is on the map
				if ((row + 1) < brd.getSizeRow())
				{
					brd.setTileValue(row, column, "-");   //change the current tile's value to black
					direction = "south";                  //change the ant's direction
					row += 1;                             //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps       
				}
				//if the next move is off the map, perform a wrap around and have the ant come out of the top of the board
				else
				{
					brd.setTileValue(row, column, "-");   //change the current tile's value to black
					direction = "south";                  //change the ant's direction
					row = 0;                              //move the ant
					temp = brd.getTileValue(row, column); //set the temporary variable equal to the new tile's value
					brd.setTileValue(row, column, "*");   //update the board with the ant's new position
					usleep(pauseTime);                    //pause
					cout << "\033[2J\033[1;1H" << endl;   //clear the current game board
					brd.print();                          //print the updated game board
					brd.setTileValue(row, column, temp);  //set the new tile back to its original value
					currentStep += 1;                     //add one to the ant's current steps
				}
			}
		}
	} while (currentStep < totalSteps); 

	//notify the user that the ant has finished moving
	cout << endl << "The ant has finished its route after " << currentStep << " steps." << endl << endl;
}