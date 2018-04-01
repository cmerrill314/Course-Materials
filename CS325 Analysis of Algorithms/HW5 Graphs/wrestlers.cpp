/*******************************************************************************************************
** Author: Christopher Merrill
** Date: 11/5/2017
** Description: CS325 Homework 5 Implementation
*******************************************************************************************************/
#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <ctgmath>
using namespace std;

vector<string> wrestlerNames; //Contains the names of each wrestler
vector<string> teams(100);    //Contains team names for each wrestler

int getWrestlerIndex(string x);
void addEdge(vector<int> adj[], int x, int y);
void BFS(int x, vector<int> adj[], vector<bool> &visited);
void setTeamNames(vector<int> adj[], int V);
 
// Driver code
int main(int argc, char *argv[]) {
    ifstream inFile;                  //Input file 
	string line;                      //Holds a line of numbers from the input file
	bool isPossible = true;           //Whether or not the graph is possible to solve
	vector< vector<string> > data;    //A vector of vectors. The inner vectors are the lines in the input file
	vector< vector<int> > rivalries;  //A vecter of vectors representing rivalries
	int i, j, numWrestlers, numRivalries, count;    
	
	//Open the input file for reading 
	inFile.open(argv[1]);
	
	//Check to make sure inFile is valid
	if (inFile) {	
	
		//Read all values in from the input file
		while (getline(inFile, line)) {
			//Push lines to the activites vector
			istringstream is(line);
			data.push_back(vector<string>(istream_iterator<string>(is), istream_iterator<string>()));
		}
		
		//Close the input file
		inFile.close();

		numWrestlers = stoi(data[0][0]);
		numRivalries = stoi(data[numWrestlers + 1][0]);
		
		//Add wrestlers to wrestlers array
		for (i = 1; i <= numWrestlers; i++) {
			wrestlerNames.push_back(data[i][0]);
		}
		
		count = 0;
		
		//Add rivalries to rivalries array
		for (i = (numWrestlers + 2); i <= (numWrestlers + numRivalries + 1); i++) {	
			vector<int> newColumn;
			rivalries.push_back(newColumn);
			rivalries.at(count).push_back(getWrestlerIndex(data[i][0]));
			rivalries.at(count).push_back(getWrestlerIndex(data[i][1]));
			count++;
		}
		
		//Create Rivalry Graph
		vector<int> graph[numWrestlers];
		
		//Add rivalry edges
		for (i = 0; i < rivalries.size(); i++) {
			addEdge(graph, rivalries[i][0], rivalries[i][1]);
		}
		
		//Determine if each wrestler should be a babyface or heel		
		setTeamNames(graph, numWrestlers);
		
		//Check for failing conditions
		for (i = 0; i < rivalries.size(); i++) {
			string teamA; //Wrestler A's Team Name
			string teamB; //Wrestler B's Team Name
			
			//Set teamA and teamB's names
			for (j = 0; j < wrestlerNames.size(); j++) {
				if (rivalries[i][0] == j)
					teamA = teams[j];
				else if (rivalries[i][1] == j)
					teamB = teams[j];
			}
			
			//If wrestler A and Wrestler B are on the same team, the problem is impossible to solve
			if (teamA == teamB) {
				isPossible = false;
			}
		}
		
		//Display results if the graph is solvable
		if (isPossible) {
			cout << "Yes" << endl;
			cout << "BabyFaces: ";
			
			for (i = 0; i < teams.size(); i++) {
				if (teams[i] == "BabyFace")
					cout << wrestlerNames[i] << " ";
			}
			
			cout << endl;
			cout << "Heels: ";
			
			for (i = 0; i < teams.size(); i++) {
				if (teams[i] == "Heel")
					cout << wrestlerNames[i] << " ";
			}
			
			cout << endl;
		}
		//Otherwise display "No"
		else {
			cout << "No..." << endl;
		}
	}
	return 0;
}

/*******************************************************************************************************
** This function retrieves the index of a particular wrestler name
*******************************************************************************************************/
int getWrestlerIndex(string x) {
	int i;
	
	//Search wrestlerNames for the passed string and return its index
	for (i = 0; i < wrestlerNames.size(); i++) {
		if (x == wrestlerNames[i])
			return i;
	}
}

/*******************************************************************************************************
** This function adds an edge to the rivalry graph
*******************************************************************************************************/
void addEdge(vector<int> adj[], int x, int y)
{
    adj[x].push_back(y);
	adj[y].push_back(x);
}

/*******************************************************************************************************
** This function performs a BFS on a passed graph starting at vertex u,
** then updates the team name for each wrestler depending on its depth
*******************************************************************************************************/
void BFS(int x, vector<int> adj[], vector<bool> &visited)
{
	int d;
 
    //Create queues
    list<int> wrestlers;        //Queue of wrestlers
	list<int> distance; //Queue of distances to wrestlers
  
    //Mark the current node as visited and queue it
    visited[x] = true;
    wrestlers.push_back(x);
	
	//Add 0 as the first distance
	distance.push_back(0);
  
    //Loop through the wrestler queue
    while(!wrestlers.empty())
    {
        //Dequeue a vertex from queues for examination
        x = wrestlers.front();
        wrestlers.pop_front();
		d = distance.front();
		distance.pop_front();
		
		//Update team names depending on if distance is even or odd
		if ((d + 1) % 2 == 0) 
			teams.at(x) = "Heel";
		else
			teams.at(x) = "BabyFace";
		
        //Examine all adjacent vertices of vertex x. 
        for (int i = 0; i != adj[x].size(); ++i)
        {
			//If an adjacent has not been visited, mark it visited and enqueue it
            if (!visited[adj[x][i]])
            {
                visited[adj[x][i]] = true;
                wrestlers.push_back(adj[x][i]);
				distance.push_back(d + 1);//Update distance
            }
        }
    }
}
 
/*******************************************************************************************************
** This function performs BFS on graph adj of size V for all unvisited vertices.
*******************************************************************************************************/
void setTeamNames(vector<int> adj[], int V){
	int i;
	
	//Initialize all verteces as not visited
    vector<bool> visited(V, false);
	
	//Loop through each vertex, perform BFS if it has not been visited
    for (i = 0; i < V; i++) {
		if (visited[i] == false)
            BFS(i, adj, visited);
	}
}