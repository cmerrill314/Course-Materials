/*******************************************************************************************************
** Authors: Christopher Merrill, Debra Wilkie, Kyle Wollman
** Date: 11/27/2017
** Description: Nearest Neighbor Implementation for Travelling Salesman Problem
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
#include <stdlib.h>
#include <time.h>
using namespace std;
   
//Function Declarations   
int nearestNeighbor(vector< vector<int> > &G, vector<int> &r); 
bool areAllVisited(vector< vector<int> > G);

int main(int argc, char *argv[]) {	
	ifstream inFile;                    //Input file 
	ofstream outFile;                   //Output file
	string outFileName = "";            //The name of the output file
	string line;                        //Holds a line from the input file
	vector< vector<int> > cities;       //A vector of vectors to hold city data from the input file
	vector<int> route;                  //Holds the ID's of each city in the salesman's route (in order)
	int i, pathLength;                  //The total length of the salesman's path            
    float total;                        //time to execute nn algorithm
    clock_t t1, t2;                     //starting and ending times
    
	//Initialzie random seed
    srand(time(NULL));

	//Construct outFileName
	outFileName += argv[1];
	outFileName += ".tour";
	
	//Open the input file for reading and output file for writing
	inFile.open(argv[1]);
	outFile.open(outFileName);
	
	//Check to make sure inFile is valid
	if (inFile) {	
	
		//Retrieve all lines of the input file and add them to the cities vector
		while (getline(inFile, line)) {
			//Push lines to the cities vector
			istringstream is(line);
			cities.push_back(vector<int>(istream_iterator<int>(is), istream_iterator<int>()));
		}
		
		//Close the input file
		inFile.close();
		
		//Initialize all cities as "Not Visited" (vector value 3 is 0)
		for (i = 0; i < cities.size(); i++) {
			cities[i].push_back(0);
		}
		
        //Start clock
        t1 = clock();

		//Run Nearest Neighbor Algorithm
		pathLength = nearestNeighbor(cities, route);
        
        //Stop clock
        t2 = clock();

        //Calculate time in seconds
        total = ((float)t2 - (float)t1);
        float seconds = total / CLOCKS_PER_SEC;

        cout << "Time to execute Nearest Neigbhor: " << seconds << " seconds." << endl;
		
        //Add results to outFile
		outFile << pathLength << endl;
		
		for (i = 0; i < route.size(); i++) {
			outFile << route[i] << endl;
		}
		
		//Close the output file
		outFile.close();
	}
	
	return 0;
}

/*******************************************************************************************************
**                                           nearestNeighbor
**
** Uses the Nearest Neighbor greedy approximation to the TSP to create a route for the salesman and 
** return the total length of that route. The idea is as follows:
**
** Input: G = pointer to a vector of int vectors which represents the Graph in question
**        r = pointer to an int vector that represents the route the salesman will take
**
** Output: Returns the length of the total path, and also updates the passed route vector as well as 
**         the "is visited" value of each vertex in G.  
*******************************************************************************************************/
int nearestNeighbor(vector< vector<int> > &G, vector<int> &r) {
	vector<int> currentVertex;          //Choose starting vertex
	bool allVisited = false;            //Initially all verticies haven't been visited  
	int shortestPath;                   //Holds the current shortest path
	float distance;                     //Distance to the next vertex
	int length = 0;                     //Initialize overall path length to 0
	int i, nn, roundDist, startCity;    //nn is the index of the nearest neighbor
    
        //calculate starting city
    startCity = rand() % G.size(); 
    currentVertex = G[startCity];    
    
    //Push starting vertex ID to r
    r.push_back(currentVertex[0]); 
    
    //Mark the current vertex as visited
    G[startCity][3] = 1;
    
    //Continue adding paths until all verticies have been visited
    while(!allVisited) {
        
        //Set shortestPath to infinity
        shortestPath = INFINITY; 
        
        //Loop through each vertex to find the shortest path from CurrentVertex to a vertex V
        for (i = 0; i < G.size(); i++) {
            
            //Exclude visited verticies from the check
            if (G[i][3] == 0) {
                
                //Calculate the distance from the current vertex to G[i]
                distance = sqrt(pow((currentVertex[1] - G[i][1]), 2.0) + pow((currentVertex[2] - G[i][2]), 2.0));
                roundDist = round(distance);
                //Update shortest path and nearest neighbor if applicable
                if (roundDist < shortestPath) {
                    shortestPath = roundDist;
                    nn = i;
                }
            }
        }
        
        //Set currentVertex to be the nearest neighbor
        currentVertex = G[nn];
        
        //Mark the new current vertex as visited
        G[nn][3] = 1;
            
        //Add nearest neighbor path length to length
        length += shortestPath;
        
        //Push the currentVertex ID to r
        r.push_back(currentVertex[0]); 
        
        //Check if all vertices have been visited
        allVisited = areAllVisited(G);	
    }
    
    //calculate the distance from the last city back to the start city
    distance = sqrt(pow((G[nn][1] - G[0][1]), 2.0) + pow((G[nn][2] - G[0][2]), 2.0));
    roundDist = round(distance);

    //add the final distance to the tour
    length += roundDist;

    return length;
}

/*******************************************************************************************************
**                                           areAllVisited
**
** Checks whether or not all verticies in a passed graph have been visited
**
** Input: G = graph to be checked
**
** Output: Returns true if all verticies have been visited, otherwise returns false.
*******************************************************************************************************/
bool areAllVisited(vector< vector<int> > G) {
	int i;
	
	//Loop through each vertex
	for (i = 0; i < G.size(); i++) {
		//Return false if a vertex hasn't been visited
		if (G[i][3] == 0) {
			return false;
		}
	}
	
	//Return true if all verticies have been visited
	return true;
}
