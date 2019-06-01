#include <iostream>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "Node.h"
#include <limits.h>

using namespace std;

/*Graph creator-

  Program with directed graphs, with weighted edges. Shortest path can be found 
  using Dijkstra's algorithm. An adjacency table is used to print the graph

  Commands:
  
  addvertex- name and add a new vertex
  addedge- create an edge with a weight to link two vertex labels
  removevertex- remove vertex label and all edges on the vertex
  removeedge- enter two vertex labels to remove edge
  findpath- use Dijkstra's algorithm to find the path with the least weight and total
  print- print an adjacency table to depict the graph
  exit- exit the program

 */
#define V 20
static float noEdge = INT_MAX; // -99;

void addVertex(char* vertex[20], int &vertexCount, char vertexInput[20]);
void printGraph(char* vertex[20], float adTable[20][20]);
void addEdge(char* vertex[20], float adTable[20][20], float weight, char firstVertex[20], char secondVertex[20]);
void removeEdge(float adTable[20][20], char firstVertex[20], char secondVertex[20], char* vertex[20]);
void removeVertex(char* vertex[20], char removedVertex[20], float adTable[20][20]);
int  lookupVertex(char* vertex[20], char vertexInput[20]);
void findPath(char* vertex[20], float adTable[20][20], char firstVertex[20], char secondVertex[20]);
void printPath(Node* destination, char* vertex[20], float &totalWeight, float adTable[20][20]);
int  minDistance(int dist[], bool sptSet[]);
void printPath(int parent[], int j, int src);
void dijkstra(float graph[V][V], int src, int src2);

char* vertex[20];

int main(){

  int vertexCount = 0;
  int inLoop = 1;
  char input[20];
  char vertexInput[20];
  float table[20][20];
//  char* vertex[20];
  char vertex1[20];
  char vertex2[20];
  float weight = 0;
    
  //Set array values to null
  for(int i = 0; i < 20; i++){
    vertex[i] = NULL;
  }

  //Initialize edge values to -99 (for no edge)
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 20; j++){
      table[i][j] = INT_MAX; // noEdge;
    }
  }
 

  //Menu
  while(inLoop == 1){
    cout << "Enter command: addvertex, addedge, removevertex, removeedge, findpath, print, exit" << endl;
    cin >> input;
    cin.ignore();
    
    if(strcmp(input, (char*)"addvertex") == 0){
      cout << "Enter vertex label for graph" << endl;
      cin >> vertexInput;   
      //cout << (char*) vertexInput << endl;
      addVertex(vertex, vertexCount, vertexInput);
    }

    if(strcmp(input, (char*)"addedge") == 0){
      cout << "Enter the label of the first vertex" << endl;
      cin >> vertex1;
      cout << "Enter the label of the second vertex" << endl;
      cin >> vertex2;
      cout << "Enter weight of edge" << endl;
      cin >> weight;
      addEdge(vertex, table, weight, vertex1, vertex2);
    }

    if(strcmp(input, (char*)"removevertex") == 0){
      cout << "Enter the label of the vertex" << endl;
      cin >> vertex1;
      removeVertex(vertex, vertex1, table);
    }

    if(strcmp(input, (char*)"removeedge") == 0){
      cout << "Enter the label of the first vertex" << endl;
      cin >> vertex1;
      cout << "Enter the label of the second vertex" << endl;
      cin >> vertex2;
      removeEdge(table, vertex1, vertex2, vertex);
      
    }

    if(strcmp(input, (char*)"findpath") == 0){
      cout << "Enter the label of the first vertex" << endl;
      cin >> vertex1;
      cout << "Enter the label of the second vertex" << endl;
      cin >> vertex2;
    //  findPath(vertex, table, vertex1, vertex2);
	  int position1 = lookupVertex(vertex, vertex1);
	  int position2 = lookupVertex(vertex, vertex2);

	  if (position1 <0) {
	    cout << "Vertex " << vertex1 << " does not exist." << endl;
	  }
	  else if (position2 <0) {
	    cout << "Vertex " << vertex2 << " does not exist." << endl;
	  }
	  else if (position1 == position2) {
	    cout << "Please pick two different vertex." << endl;
	  }
	  else {
	    //   cout << position1 << ", " << position2 << endl;	    
	   dijkstra(table, position1, position2);
	  }
    }

    if(strcmp(input, (char*)"print") == 0){
      printGraph(vertex, table);
	  
    }

    if(strcmp(input, (char*)"exit") == 0){
      inLoop = 0;
      cout << "Exited" << endl;
    }
    
  }
}

//Add a vertex
void addVertex(char* vertex[20], int &vertexCount, char vertexInput[20]){
  int check = 0;
  int length = strlen(vertexInput);

  //Check for duplicate vertex
  for(int i = 0; i < 20; i++){
    if(vertex[i] != NULL && strcmp((char*)vertex[i], (char*)vertexInput) == 0){
      check++;
    }
  }

  //There is a duplicate
  if (check > 0){
    cout << "Vertex label has already been entered" << endl;
    return;
  }

  //Add vertex label
  if (check ==0) {
    vertex[vertexCount]= new char[length + 1];
    strcpy(vertex[vertexCount], vertexInput);
    vertexCount ++;
    cout << "Vertex " << vertexInput << " is added. " << endl << endl;
  }
  
}

//Print 
void printGraph(char* vertex[20], float adTable[20][20]){
  cout << "Vertex list: ";

  //Print vertex labels
  for(int i = 0; i < 20; i++){
    if(vertex[i] != NULL){
      cout << vertex[i] << ", ";
    }
  }
  cout << endl;

  cout << "Adjacent table for the edges: " << endl;
  //Print top vertices (as label for the column) 
  cout << "       ";
  for(int i = 0; i < 20; i++){
    if(vertex[i] != NULL){
      printf("%7s ", vertex[i]);
    }
  }
  cout << endl;
  
  //Print edges
  for(int i = 0; i < 20; i++){
    if(vertex[i] != NULL){
      printf("%7s ", vertex[i]);

      // print the columns with weight: 
      for(int j = 0; j < 20; j++){
	if(vertex[j] != NULL){
	  if (adTable[i][j] < INT_MAX) { //!= noEdge) {
	      printf("%7.2f ", adTable[i][j]);
	  }
	  else {  // INT_MAX as no edge // -99 for no edge
	    printf("     .  ");
	  }
	}
      }
      cout << endl;
    }
  }

  cout << endl;
}

// lookup vertex label for the array position
int lookupVertex(char* vertex[20], char vertexInput[20]) {
  
  int position = -1;
  for (int i = 0; i < 20; i++) {
    if (vertex[i] != NULL && strcmp(vertex[i], vertexInput) ==0) {
      position =i;
      return position;
    }
  }

  return position;
}


//Function to add edge using two inputed vertex and weight
void addEdge(char* vertex[20], float adTable[20][20], float weight, char firstVertex[20], char secondVertex[20]){
  
  int position1 = -1;
  int position2 = -1;

  //Find first index of the vertex
  for(int i = 0; i < 20; i++){
    if(vertex[i] != NULL && strcmp(vertex[i], firstVertex) == 0){
      position1 = i;
      break;
    }
  }

  //Find second index of the vertex
   for(int i = 0; i < 20; i++){
    if(vertex[i] != NULL && strcmp(vertex[i], secondVertex) == 0){
      position2 = i;
      break;
    }
  }

   //Make sure vertex names are entered correctly
   if(position1 > -1 && position2 > -1){
     adTable[position1][position2] = weight;
     // cout << adTable[position1][position2] << endl;
   }
   
   else{
     cout << "Not valid vertex" << endl;
   }
}


//Remove edge between two vertices
void removeEdge(float adTable[20][20], char firstVertex[20], char secondVertex[20], char* vertex[20]){
  int position1 = -1;
  int position2 = -1;
   //Find first index of the vertex
  for(int i = 0; i < 20; i++){
    if(vertex[i] != NULL && strcmp(vertex[i], firstVertex) == 0){
      position1 = i;
      break;
    }
  }

  //Find second index of the vertex
   for(int i = 0; i < 20; i++){
    if(vertex[i] != NULL && strcmp(vertex[i], secondVertex) == 0){
      position2 = i;
      break;
    }
  }

   //Clear the edge between the two vertices
   if(position1 > -1 && position2 > -1){
     adTable[position1][position2] = INT_MAX; // noEdge;
   }

   else{
     cout << "Not valid vertex" << endl;
   }

}

//Remove vertex and all edges to that vertex
void removeVertex(char* vertex[20], char removedVertex[20], float adTable[20][20]){
  int check = 0;
  int position = -1;
  
  //Find the vertex to be removed; find position of removed vertex
  for(int i = 0; i < 20; i++){
    if(vertex[i] != NULL && strcmp((char*)vertex[i], (char*)removedVertex) == 0){
      position = i;
      check++;
      break;
    }
  }

  //The label is there, clear all edges to the removed vertex and remove vertex
  if (check > 0){
    delete vertex[position];
    vertex[position] = NULL;
    for(int i = 0; i < 20; i++){
      adTable[i][position] = noEdge;
    }
    
    for(int i = 0; i < 20; i++){
      adTable[position][i] = noEdge;
    }
    cout << "edges to the vertex have been cleared" << endl;
  }

  //Vertex not found
  if(check == 0) {
    cout << "The vertex was not found" << endl;
    return;
  }

}

//Breadth-first search
void findPath(char* vertex[20], float adTable[20][20], char firstVertex[20], char secondVertex[20]){

  //Initialize visited array to false
  bool visited[20];
  for(int i = 0; i < 20; i++){
    visited[i] = false;
  }
  
  //Find position of both vertices
  int position1 = lookupVertex(vertex, firstVertex);
  int position2 = lookupVertex(vertex, secondVertex);

  if(position1 < 0 || position2 < 0){
    cout << "Not valid vertices" << endl;
    return;
  }

  Node* head = new Node;
  head->setValue(position1);
  Node* tail = head;
  Node* current = head;
  Node* destination = NULL;
  int inLoop = 1;
  visited[position1] = true;
  
  while(inLoop == 1){
    for(int i = 0; i < 20; i++){
      if(adTable[current->getValue()][i] != INT_MAX && visited[i] == false){
	Node* n = new Node;
	n->setParent(current);
	n->setValue(i);
	tail->setNext(n);
	tail = n;

	//Vertex2 found
	if(position2 == i){
	  destination = n;
	  inLoop = 0;
	}

	
      }
      
    }
    current = current->getNext();
    if(current == NULL){
      inLoop = 0;
    }
    
  }
  
  //No path found
  if(destination == NULL){
    cout << "No path found" << endl << endl;
  }

  //Path found
  else{
    float totalWeight = 0;
    cout << "Path found: ";
    printPath(destination, vertex, totalWeight, adTable);
    cout << endl << "Total Weight: " << totalWeight << endl << endl;
  }
}

void printPath(Node* destination, char* vertex[20], float &totalWeight, float adTable[20][20]){
  
  if(destination == NULL){
    return;
  }
  else{
    printPath(destination->getParent(), vertex, totalWeight, adTable);
    if(destination->getParent() != NULL){
      totalWeight = totalWeight + adTable[destination->getParent()->getValue()][destination->getValue()];
      cout << "->";
    }
    cout << vertex[destination->getValue()];
  }
}

float minDistance(float dist[], bool sptSet[])
{
	// Initialize min value 
	int min = INT_MAX;
	int min_index = -1;
	for (int v = 0; v < V; v++)
	    if (sptSet[v] == false && dist[v] < min)
	    {
		min = dist[v];
	        min_index = v;
            }
	
	return min_index;
}

// Function to print shortest path from source to j using parent array 
void printPath(int parent[], int j, int src)
{

	// Base Case : If j is source 
	if (j==-1 || parent[j] == -1 || j == src)
	   return;

	printPath(parent, parent[j], src);

	//	printf("%d ", j);
	printf("%s ", vertex[j]);	
}

// A utility function to print the constructed distance array 
int printSolution(float dist[], int parent[], int src, int dest)
{
        //int src = 0;
  	printf("Find Dijkstra's shortest path:\n");
	/* 	for (int i = 1; i < V; i++)
	{
		printf("\n%d -> %d \t\t %f\t\t%d ",
			src, i, dist[i], src);
	        printPath(parent, i);
	}
	*/

	if (dist[dest] > INT_MAX -1000)
	 {
	    cout << endl << "No path found. " << endl;
	    return 0;
	 }
	
	// printf("\n%d -> %d \t\t %7.2f\t\t%d ", src, src2, dist[src2], src);
	printf("%s->%s, distance: %5.2f, path: %s ",
	       vertex[src], vertex[dest], dist[dest], vertex[src]);
        printPath(parent, dest, src);
	
}

// Funtion that implements Dijkstra's 
// single source shortest path 
// algorithm for a graph represented 
// using adjacency matrix representation 
void dijkstra(float graph[V][V], int src, int dest)
{
	// The output array. dist[i] 
	// will hold the shortest distance from src to i 
	float dist[V];

	// sptSet[i] will true if vertex 
	// i is included / in shortest 
	// path tree or shortest distance 
	// from src to i is finalized 
	bool sptSet[V];

	// Parent array to store 
	// shortest path tree 
	int parent[V];

	// Initialize all distances as  
	// INFINITE and stpSet[] as false 
	for (int i = 0; i < V; i++)
	{
		parent[0] = -1;
		dist[i] = INT_MAX; //noEdge
		sptSet[i] = false;
	}

	// Distance of source vertex from itself is always 0 
	dist[src] = 0;

	// Find shortest path 
	// for all vertices 
	for (int count = 0; count < V; count++)
	{
	    // Pick the minimum distance vertex from the set of 
	    // vertices not yet processed.  
	    // u is always equal to src in first iteration. 
	    int u = minDistance(dist, sptSet);

	    if (u>=0)
	    {	      
		// Mark the picked vertex  as processed 
		sptSet[u] = true;

		// Update dist value of the 
		// adjacent vertices of the 
		// picked vertex. 
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is 
			// not in sptSet, there is 
			// an edge from u to v, and  
			// total weight of path from 
			// src to v throug
			if (!sptSet[v] && graph[u][v] < INT_MAX &&
				dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}

	    } // end if 
	  }

	// print the constructed 
	// distance array 
	printSolution(dist, parent, src, dest);
	cout << endl;
	
}
