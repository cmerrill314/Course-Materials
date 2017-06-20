/*
Christopher Merrill
4/25/2017
CS290
HW Assignment: Higher-Order Functions and Objects

Description: This program sorts an array of automobiles by year, make and type using Higher-Order Functions

*/

function Automobile(year, make, model, type ){
    this.year = year;   //integer (ex. 2001, 1995)
    this.make = make;   //string (ex. Honda, Ford)
    this.model = model; //string (ex. Accord, Focus)
    this.type = type;   //string (ex. Pickup, SUV)
	
	//The log me function prints the values above to the console. 
	this.logMe = function(arg) {
		//If arg is true, display the type. Otherwise omit the type.
		if (arg) {
			console.log(this.year + " " + this.make + " " +this.model + " " +this.type);
		}
		else {
			console.log(this.year + " " +this.make + " " +this.model);
		}
	}
}

var automobiles = [ 
    new Automobile(1995, "Honda", "Accord", "Sedan"),
    new Automobile(1990, "Ford", "F-150", "Pickup"),
    new Automobile(2000, "GMC", "Tahoe", "SUV"),
    new Automobile(2010, "Toyota", "Tacoma", "Pickup"),
    new Automobile(2005, "Lotus", "Elise", "Roadster"),
    new Automobile(2008, "Subaru", "Outback", "Wagon")
    ];

/*This function sorts arrays using an arbitrary comparator. You pass it a comparator and an array of objects appropriate for that 
comparator and it will return a new array which is sorted with the largest object in index 0 and the smallest in the last index*/
function sortArr(comparator, array ){
	var newArr = [];       //This will hold the new, sorted array
	var count = 0;         //The number of items in the passed array
    var swapped = true;    //Used in the bubble sort below
	var j = 0;             //Used in the bubble sort below
	var temp;              //Used in the bubble sort below
	var comparatorResults; //Used in the bubble sort below
	
	//First populate the new array with the unsorted contents of the original array
	array.forEach(function addContents(val, index){
		newArr.push(array[index]);
		count++; //Increment the count as each item is added
	})
	
	//Sort the new array with a bubble sort. 
	//**Note: This bubble sort is based on the algorithm found here: http://www.algolist.net/Algorithms/Sorting/Bubble_sort
	while(swapped) {
		swapped = false;
		j++;
		for (var i = 0; i < count - j; i++) {
			comparatorResults = comparator(newArr[i], newArr[i + 1]);
			if (!comparatorResults) {
				temp = newArr[i];
				newArr[i] = newArr[i + 1];
				newArr[i + 1] = temp;
				swapped = true;
			}
		}
	}
	
	//Return the sorted array
	return newArr;
}

/*This compares two automobiles based on their year. Newer cars are "greater" than older cars.*/
function yearComparator(auto1, auto2){
    if (auto1.year > auto2.year) {
		return true;
	}
	else {
		return false;
	}
}

/*This compares two automobiles based on their make. It should be case insensitive and makes which are 
alphabetically earlier in the alphabet are "greater" than ones that come later.*/
function makeComparator(auto1, auto2){
    //Convert the makes to lowercase to assure the comparator is case insensitive
	var aMake = auto1.make.toLowerCase();
	var bMake = auto2.make.toLowerCase();
	
	if (aMake < bMake) {
		return true;
	}
	else {
		return false;
	}
}

/*This compares two automobiles based on their type. The ordering from "greatest" to "least" is as follows: 
roadster, pickup, suv, wagon, (types not otherwise listed). It should be case insensitive. 
If two cars are of equal type then the newest one by model year should be considered "greater".*/
function typeComparator(auto1, auto2){
	//This function assigns numerical values that corresponding type of automobile
	var assignValue = function(auto) {
		if (auto.type == "Roadster") 
			return 4;
		else if (auto.type == "Pickup") 
			return 3;
		else if (auto.type == "SUV") 
			return 2;
		else if (auto.type == "Wagon") 
			return 1;
		else 
			return 0;
	}
	
	//Assign numerical values to auto1 and auto2's type
	var aType = assignValue(auto1);
	var bType = assignValue(auto2);
	
	//Compare values
	if (aType == bType) {
		//In the case of equal types, use the year comparator to determine which automobile is "greater"
		var yearTest = yearComparator(auto1, auto2);
		
		if (yearTest) 
			return true;
		else 
			return false
	}
	else if (aType > bType) 
		return true;
	else 
		return false;
}

/*This displays the each version of the sorted results of an array: by year, by make and by type */
function displayResults(array) {
	//This function prints 5 stars to the console
	var displayStars = function() {console.log("*****");}
	
	//This function displays a title followed by the contents of an array
	var displayList = function(array, name) {
		//Display the title
		console.log("The cars sorted by " + name + " are:");
		//Display the array contents
		array.forEach(function display(val) {
			if (name == "year" || name == "make") 
				val.logMe(false);
			else
				val.logMe(true);
		})
	}
	
	//Display the results of each sorted version of the array
	displayStars();
	displayList(sortArr(yearComparator, array), "year");
	console.log("");
	displayList(sortArr(makeComparator, array), "make");
	console.log("");
	displayList(sortArr(typeComparator, array), "type");
	displayStars();
}

//Display the results
displayResults(automobiles);