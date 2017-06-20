/*
Christopher Merrill 
CS290
5/30/2017
HW Assignment: Database Interactions and UI

Description: This file contains all of the client side interations for the Workout Tracker
*/

document.addEventListener('DOMContentLoaded', bindButtons);
var port = "8386"; //This allows for easy port changing

//Reset the table when the page loads
resetTable();      

/*This function controls the behavior carried out when the "Add" button is pressed */
function bindButtons(){
	//Add Value Function:
	document.getElementById('add').addEventListener('click', function(event) {
		//Create a new HTTP request
		var req = new XMLHttpRequest();  

		//Get the data from the form to use in the URL
		var nameValue = document.getElementById('name').value; 
		var repsValue = document.getElementById('reps').value;  
		var weightValue = document.getElementById('weight').value; 
		var dateValue = document.getElementById('date').value; 
		var lbsValue = document.getElementById('lbs').value; 
		
		//Contruct a URL that sends a GET request to /insert with all of the necessary data
		var url = "http://flip2.engr.oregonstate.edu:" + port + "/insert?" + "name=" + nameValue + "&reps=" + repsValue + "&weight=" + weightValue + "&date=" + dateValue + "&lbs=" + lbsValue; 
		
		//Make the call
		req.open("GET", url, false); 
		req.addEventListener('load',function(){
			//If the request status is valid, update the table with the new value
			if(req.status >= 200 && req.status < 400){
				console.log(req.responseText); 
				
				//Update the table
				updateTable(); 
			} 
			//If the request status isn't valid, display an error message with the request status
			else {
				console.log("Error in network request: " + req.statusText);
			}});				
		req.send(null);         //no need to send additional data
		event.preventDefault(); //prevent the page from refreshing
	});
}

/*This function sends an AJAX request to refresh the database, it is used when the page loads*/
function resetTable() {
	var req = new XMLHttpRequest();  
	var url = "http://flip2.engr.oregonstate.edu:" + port + "/reset-table";
	req.open("GET", url, false); 
		req.addEventListener('load',function(){
			//If the request status is valid, log a confirmation message to the console 
			if(req.status >= 200 && req.status < 400){
				console.log(req.responseText);
			} 
			//If the request status isn't valid, display an error message with the request status
			else {
				console.log("Error in network request: " + req.statusText);
			}});	
	req.send(null); //no need to send additional data
}

/*This function updates the table on the page. It uses an AJAX request to /select-table to pull the current status of the database*/
function updateTable() {
	var req = new XMLHttpRequest();  
	var url = "http://flip2.engr.oregonstate.edu:" + port + "/select-table";
	req.open("GET", url, false); 
		req.addEventListener('load',function(){
			//If the request status is valid, update the table
			if(req.status >= 200 && req.status < 400){
				//Parse the JSON response
				var response = JSON.parse(req.responseText); 
				
				//Delete old table contents
				deleteTableContents("workouts");
				
				//Add new table contents;
				addTableContents("workouts", response);
			} 
			//If the request status isn't valid, display an error message with the request status
			else {
				console.log("Error in network request: " + req.statusText);
			}});	
	req.send(null); //no need to send additional data
}

/* This function is used to add the database contents to the table. It is called in the updateTable function above */
function addTableContents(tableID, object) {
	//Add a new row to the for each member of the passed object
	for (i = 0; i < object.length; i++) {
		
		//Insert a new row
		var row = document.getElementById(tableID).insertRow(i + 1);
		
		//Insert a new cell for each column
		var name = row.insertCell(0);
		var reps = row.insertCell(1);
		var weight = row.insertCell(2);
		var date = row.insertCell(3);
		var lbs = row.insertCell(4);
		var edit = row.insertCell(5);
		var del = row.insertCell(6);
		
		//Update the HTML in each new cell
		name.innerHTML = object[i].name;
		reps.innerHTML = "<center>" + object[i].reps + "</center>";	
		weight.innerHTML = "<center>" + object[i].weight + "</center>";
		date.innerHTML = "<center>" + object[i].date + "</center>";
		lbs.innerHTML = "<center>" + object[i].lbs + "</center>";
		edit.innerHTML = "<form class='form'><label>Name:</label><input type='text' value='" + object[i].name + "' name='name' id='name" + object[i].id + "'><br><label>Reps:</label><input type='number' value='" + object[i].reps + "' name='reps' id='reps" + object[i].id + "'><br><label>Weight:</label><input type='number' value='" + object[i].weight + "' name='weight' id='weight" + object[i].id + "'><br><label>Date:</label><input type='text' value='" + object[i].date + "' name='date' id='date" + object[i].id + "'><br><label>lbs:</label><input type='number' value='" + object[i].lbs + "' name='lbs' id='lbs" + object[i].id + "'><br><br><input type='submit' value='Edit' class='submit' onclick='editTableRow(" + object[i].id + ")'></form>";
		del.innerHTML = "<form><input type='submit' value='Delete' class='submit' onclick='deleteTableRow(" + object[i].id + ")'></form>";
	}
}

/* This function clears the contents of the table on the browser. It is used in conjuction with the addTableContents function above to update the table when an item is added or deleted */
function deleteTableContents(tableID) {
	//Delete all rows besides the header row
	if (document.getElementById(tableID).rows.length > 1) {
		//Delete the table rows in reverse order to avoid missing rows
		for (i = (document.getElementById(tableID).rows.length - 1); i > 0; i--) {
			document.getElementById(tableID).deleteRow(i);
		}
	}
}

/* This function sends an AJAX request to /insert in order to edit a rows contents. It is executed when a row's edit button is pressed */
function editTableRow(id) {
	//Create a new HTTP request
	var req = new XMLHttpRequest(); 
 
	//Get the data from the form to use in the URL
	var nameValue = document.getElementById('name' + id).value; 
	var repsValue = document.getElementById('reps' + id).value;  
	var weightValue = document.getElementById('weight' + id).value; 
	var dateValue = document.getElementById('date' + id).value; 
	var lbsValue = document.getElementById('lbs' + id).value;
	
	//Contruct a URL that sends a GET request to /update with all of the necessary data
	var url = "http://flip2.engr.oregonstate.edu:" + port + "/update?" + "name=" + nameValue + "&reps=" + repsValue + "&weight=" + weightValue + "&date=" + dateValue + "&lbs=" + lbsValue + "&id=" + id; 
	
	//Make the call
	req.open("GET", url, false); 
	req.addEventListener('load',function(){
		//If the request status is valid, update the table
		if(req.status >= 200 && req.status < 400){
			console.log(req.responseText); 
			updateTable();
		} 
		//If the request status isn't valid, display an error message with the request status
		else {
			console.log("Error in network request: " + req.statusText);
		}});	
		
	req.send(null);         //no need to send additional data	
	event.preventDefault(); //prevent the page from refreshing
}

/* This function sends an AJAX request to /delete in order to delete a row from the table. It is excuted when a row's delete button is pressed */
function deleteTableRow(id) {
	//Create a new HTTP request
	var req = new XMLHttpRequest();   
	
	//Contruct a URL that sends a GET request to /delete with the id value
	var url = "http://flip2.engr.oregonstate.edu:" + port + "/delete?id=" + id; 
	
	//Make the call
	req.open("GET", url, false); 
	req.addEventListener('load',function(){
		//If the request status is valid, update the table
		if(req.status >= 200 && req.status < 400){
			console.log(req.responseText); 
			updateTable();
		} 
		//If the request status isn't valid, display an error message with the request status
		else {
			console.log("Error in network request: " + req.statusText);
		}});	
		
	req.send(null);         //no need to send additional data
	event.preventDefault(); //prevent the page from refreshing
}

