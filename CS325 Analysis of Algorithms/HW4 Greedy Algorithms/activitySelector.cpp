/*******************************************************************************************************
** Author: Christopher Merrill
** Date: 10/17/2016
** Description: This program builds an optimal schedule of activities, considering that each activity 
** needs to occupy a shared space. It utilizes a greedy algorithm, selectActivities, that starts with 
** the activity with the latest start time. It then works its way backwards from there to build the 
** schedule. 
*******************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <ctgmath>
using namespace std;

//Function declarations
void selectActivities (vector< vector<int> > a);
void bubbleSort(vector< vector<int> >& a);
void swap(vector<int> *x, vector<int> *y);

int main()
{
	ifstream inFile;                  //Input file act.txt
	string line;                      //Holds a line of numbers from act.txt
	vector< vector<int> > data;       //A vector of vectors. The inner vectors are the lines in act.txt
	vector< vector<int> > activities; //A set of activities. Inner vectors hold start and finish times
	int i, j, n, start, end, row = 0, set = 1;    
	
	//Open the input file for reading 
	inFile.open("act.txt");
	
	//Check to make sure inFile is valid
	if (inFile) {	
	
		//Read all values in from the input file
		while (getline(inFile, line)) {
			//Push lines to the activites vector
			istringstream is(line);
			data.push_back(vector<int>(istream_iterator<int>(is), istream_iterator<int>()));
		}
		
		//Close the input file
		inFile.close();
		
		//Loop through each set of activities until the end of the input file is reached
		while (row < data.size()) {
			
			//Set n and determine the loaction of the first and last activity 
			n = data[row][0];
			start = row + 1;
			end = row + n;
			
			//Push the activities into the activities vector
			for (i = start; i <= end; i++) {
				activities.push_back(data[i]);
			}
			
			//Sort the activites into descending start times
			bubbleSort(activities);
			
			//Create Schedule using selectActivities
			cout << "Set: " << set << endl;
			selectActivities(activities);
			
			//Clear activities vector
			activities.clear();
			
			//Increment row and set
			row = row + n + 1;
			set++;
		}			
	}
    return 0;
}

/*******************************************************************************************************
selectActivities

Input: A list of activities presorted by start time in descending order.
Output: Displays the results of which activities to add to the schedule and in which order. 

Description: Given a list of activities, this function builds an optimal schedule of which activities
should occupy a given shared space. It starts by adding the activity with the latest start time, and 
then continues adding activities with the latest start time who finish before the previously added 
activity.  
*******************************************************************************************************/
void selectActivities (vector< vector<int> > a) {
	int m, k = 0, n = a.size();
	vector< vector<int> > schedule;
	
	//Add the first value to the end of the schedule, since it has the latest start time
	schedule.push_back(a[0]);

	//Add activies to schedule whose finish time is before the previous activities start time
	for (m = 1; m < n; m++) { 
		//If the next activity finishes before the previously added activity starts, add it. 
		if (a[m][2] <= schedule[k][1]) {
			schedule.push_back(a[m]);
			k++; //increment k
		}
	}
	
	//Print Results
	cout << "Number of Activites Selected: " << schedule.size() << endl;
	cout << "Activities: ";
	for (m = schedule.size() - 1; m >= 0; m--) {
		cout << schedule[m][0] << " ";
	}
	cout << endl << endl;	
}

 
/*******************************************************************************************************
bubbleSort

Input: A list of activities 
Output: A sorted list of activites

Description: Standard bubble sort to sort the list of activities by start time in descending order. 
*******************************************************************************************************/
void bubbleSort(vector< vector<int> >& a){
	int i, j, n;
	n = a.size();
	
	//Bubble sort
	for (i = 0; i < n-1; i++) { 
		for (j = 0; j < n-i-1; j++) {
			if (a[j][1] < a[j+1][1]) {
				swap(&a[j], &a[j+1]);
			}	
		} 
	}     
}

/*******************************************************************************************************
swap

Input: Two activities to swap

Description: Swaps the location of two activities in the activity list. Used with bubbleSort.
*******************************************************************************************************/
void swap(vector<int> *x, vector<int> *y){
    vector<int> temp = *x;
    *x = *y;
    *y = temp;
}