/*
Christopher Merrill
CS290
5/2/2017
HW Assignment: DOM and Events

Description: 

This program builds a 4x4, labelled table. The user can then
traverse the table using up, down, left and right buttons. There is also a 
button to "mark" a cell, which changes the background color of the cell to 
yellow.

There are buildTable and buildButton functions that create the table and 
buttons on the page. 

The selectCell and deselectCell functions are used for selecting cells.

The functions moveUp, moveDown, moveLeft, moveRight and markCell define the
behavior of each button.

The createPage function ties all of the above functions together by constructing
the table/buttons and adding event clickers. 
*/

//Call the create page function, passing it the values of the desired number of rows and columns.
createPage(4,4);

/*
This function creates the 4x4 table and adds text content to each cell. 
The rows are created and appended to the table, and the columns are 
created and appended to the rows. 
*/
function buildTable(rows, cols) {
	//Create the table
	var newTable = document.createElement("table");
	
	//Add four rows to the table
	for(var i = 1; i < (rows + 1); i++) {
		var newRow = document.createElement("tr");
		
		//Add four columns to each row
		for(var j = 1; j < (cols + 1); j++) {
			var newCol;
			
			//If this is the first row, create header columns
			if(i == 1) {
				newCol = document.createElement("th");
				newCol.textContent = "Header " + j;  
			}
			else {
				var newCol = document.createElement("td");
				newCol.textContent = j + ", " + (i-1);
			}
			newCol.style.border = "1px solid black"; //Default border is 1px
			newRow.appendChild(newCol);
		}
		//Append the row to be a child of the table
		newTable.appendChild(newRow);
	}
	//Adjust the styling of the table
	newTable.style.border = "1px solid black"; 
	
	return newTable;  
}

/*
This function creates and returns a button element with the desired text and ID. 
*/
function buildButton(name, id) {
	var newButton = document.createElement("button");
	newButton.id = id;            //update the button ID
	newButton.textContent = name; //update the button text
	
	return newButton;
}

/*
This function "selects" a cell by thickening the cell border. It takes a table as
well as the specified row and column to select and then traverses the tables child
elements to find the correct cell.
*/
function selectCell(table, row, col) {
	rows = table.children;     //First find all children(rows) of the table element
	cols = rows[row].children; //Next find all children(columns) of the desired row
	cell = cols[col - 1];      //Pinpoint the desired column
	
	//Adjust the border thickness of the cell to 3px
	cell.style.border = "3px solid black";
}

/*
This function "deselects" a cell by thinning the cell border. It takes a table as
well as the specified row and column to select and then traverses the tables child
elements to find the correct cell.
*/
function deselectCell(table, row, col) {
	rows = table.children;     //First find all children(rows) of the table element
	cols = rows[row].children; //Next find all children(columns) of the desired row
	cell = cols[col - 1];      //Pinpoint the desired column
	
	//Adjust the border thickness of the cell to 1px
	cell.style.border = "1px solid black";
}

/*
This function selects the cell above the currently selected cell. It utilizes the 
selectCell and deselectCell functions above to achieve the desired effect.
*/
var moveUp = function(table, tracker) {
	//If the current selected cell is on the top border, do nothing
	if (tracker.curRow != 1) {
		//Deselect the current selected cell
		deselectCell(table, tracker.curRow, tracker.curCol);
		//Decrement the row value of the position tracker
		tracker.curRow--;
		//Select the desired cell
		selectCell(table, tracker.curRow, tracker.curCol);
	}
}

/*
This function selects the cell below the currently selected cell. It utilizes the 
selectCell and deselectCell functions above to achieve the desired effect.
*/
var moveDown = function(table, tracker, maxRows) {
	//If the current selected cell is on the bottom border, do nothing
	if (tracker.curRow != maxRows) {
		//Deselect the current selected cell
		deselectCell(table, tracker.curRow, tracker.curCol);
		//Increment the row value of the position tracker
		tracker.curRow++;
		//Select the desired cell
		selectCell(table, tracker.curRow, tracker.curCol);
	}
}

/*
This function selects the cell to the right of the currently selected cell. It utilizes the 
selectCell and deselectCell functions above to achieve the desired effect.
*/
var moveRight = function(table, tracker, maxCols) {
	//If the current selected cell is on the right border, do nothing
	if (tracker.curCol != maxCols) {
		//Deselect the current selected cell
		deselectCell(table, tracker.curRow, tracker.curCol);
		//Increment the column value of the position tracker
		tracker.curCol++;
		//Select the desired cell
		selectCell(table, tracker.curRow, tracker.curCol);
	}
}

/*
This function selects the cell to the left of the currently selected cell. It utilizes the 
selectCell and deselectCell functions above to achieve the desired effect.
*/
var moveLeft = function(table, tracker) {
	//If the current selected cell is on the left border, do nothing
	if (tracker.curCol != 1) {
		//Deselect the current selected cell
		deselectCell(table, tracker.curRow, tracker.curCol);
		//Decrement the column value of the position tracker
		tracker.curCol--;
		//Select the desired cell
		selectCell(table, tracker.curRow, tracker.curCol);
	}
}

/*
This function changes the background color of the desired cell to yellow. 
*/
var markCell = function(table, tracker) {
	rows = table.children;                //First find all children(rows) of the table element
	cols = rows[tracker.curRow].children; //Next find all children(columns) of the desired row
	cell = cols[tracker.curCol - 1];      //Pinpoint the desired column
	
	//Change the background color of the cell to yellow using style.backgroundColor
	cell.style.backgroundColor = "yellow";
}

/*
This function creates the web page by utilizing the above functions. It takes the desired number
of rows and columns as parameters, and these numbers can be changed freely with no effect on the 
functioning of the web page. 
*/
function createPage(rows, cols) {
	//Create a cellTracker object that keeps track of the current selected cell
	var cellTracker = {
		curRow: 1,
		curCol: 1
	};

	//Build a 4x4 table and append it to the document body
	var table = buildTable(rows, cols);
	document.body.appendChild(table);

	//Begin with cell 1,1 "selected"
	selectCell(table, cellTracker.curRow, cellTracker.curCol);
	
	//Build each of the five buttons using buildButton and append them to the document
	document.body.appendChild(buildButton("Move Up", "up"));
	document.body.appendChild(buildButton("Move Down", "down"));
	document.body.appendChild(buildButton("Move Left", "left"));
	document.body.appendChild(buildButton("Move Right", "right"));
	document.body.appendChild(buildButton("Mark Cell", "mark"));

	//Add event listeners for each button, which call the corresponding function when the button is clicked
	document.getElementById("up").addEventListener("click", function(){moveUp(table, cellTracker)});
	document.getElementById("down").addEventListener("click", function(){moveDown(table, cellTracker, (rows - 1))});
	document.getElementById("right").addEventListener("click", function(){moveRight(table, cellTracker, cols)});
	document.getElementById("left").addEventListener("click", function(){moveLeft(table, cellTracker)});
	document.getElementById("mark").addEventListener("click", function(){markCell(table, cellTracker)});
} 

















