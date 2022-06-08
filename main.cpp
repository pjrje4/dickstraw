#include <iostream>
#include <climits>
#include <cstring>

#if 0
Justin Iness
C++ Programming
6/7/22
Dijikstras Algorithm Graph
#endif

using namespace std;

int main()
{
	int graph[20][20]={  // weight maxtrix
	//      | 0|| 1|| 2|| 3|| 4|| 5|	
	//      | a|| b|| c|| d|| e|| f|
/*0*/	/*a*/	{ 0,  0,  0,  0,  0,  0},
/*1*/	/*b*/	{ 0,  0,  0,  0,  0,  0},
/*2*/	/*c*/	{ 0,  0,  0,  0,  0,  0},
/*3*/	/*d*/	{ 0,  0,  0,  0,  0,  0},
/*4*/	/*e*/	{ 0,  0,  0,  0,  0,  0},
/*5*/	/*f*/	{ 0,  0,  0,  0,  0,  0}};
	for (int i = 0; i < 20; i++) { // set all 0's to -1's
		for (int j = 0; j < 20; j++) {
			if (graph[i][j] == 0) {
				graph[i][j] = -1;
			}
		}
	}

	char input[5000];
	while (true) {
		cout << "Enter a command (ADDV), (ADDE), (DELV), (DELE), (SHORT), (PRINT), or (QUIT): " << endl;
		cin >> input;
		if (strcmp(input, "ADDV") == 0) { // addvertex
			cout << "What would you like to label the node? (a-t):  " << endl;
			cin >> input;
			int vnum = input[0] - 97; // to number
			graph[vnum][vnum] = 0;
		}
		else if (strcmp(input, "ADDE") == 0) { // addedge
			cout << "Enter the first node's name (a-t):  " << endl;
			cin >> input;
			int node1 = input[0] - 97;
			cout << "Enter the second node's name (a-t):  " << endl;
			cin >> input;
			int node2 = input[0] - 97;
			if (graph[node1][node1] != -1 && graph[node2][node2] != -1) { //if they both exist
				cout << "Enter a weight between the two nodes:  " << endl;
				int w;
				cin >> w;
				graph[node1][node2] = w; // store weight in matrix
			}
			else {
				cout << "node doesn't exist" << endl;
			}
		}
		else if (strcmp(input, "DELV") == 0) { // deletevertex
			cout << "Enter a node to delete (a-t):  " << endl;
			cin >> input;
			int n = input[0] - 97;
			for (int i = 0; i < 20; i++) { // set all connections to and from to null
				graph[n][i] = -1;
				graph[i][n] = -1;
			}
		}
		else if (strcmp(input, "DELE") == 0) { // deleteedge
			cout << "Enter the first node's name (a-t):  " << endl;
			cin >> input;
			int node1 = input[0] - 97;
			cout << "Enter the second node's name (a-t):  " << endl;
			cin >> input;
			int node2 = input[0] - 97;
			graph[node1][node2] = -1; // set connection to and from nodes to null
			graph[node2][node1] = -1;
                }
		else if (strcmp(input, "SHORT") == 0) { // shortestpath
			cout << "Enter the first node's name (a-t):  " << endl;
			cin >> input;
			int node1 = input[0] - 97;
			cout << "Enter the second node's name (a-t):  " << endl;
			cin >> input;
			int node2 = input[0] - 97;
			if (graph[node1][node1] != -1 && graph[node2][node2] != -1) { //if they exist
				//dickstraw
				bool visited[20];
				for (int i = 0; i < 20; i++) {
					visited[i] = false;
				}
				int vdist[2][20];
				for (int j = 0; j < 20; j++) {
					vdist[0][j] = INT_MAX;
					vdist[1][j] = -1;
				}
				vdist[0][node1] = 0;
				while (true) { // loop
					int currentnode = -1;
					int lowestdist = INT_MAX;
					for (int i = 0; i < 20; i++) { // lowest unvisited
						if (visited[i] == false && vdist[0][i] < lowestdist) {
							currentnode = i;
							lowestdist = vdist[0][i];
						}
					}
					if (currentnode == -1) { // if looped through all nodes
						break;
					}
					for (int i = 0; i < 20; i++) { // unvisited neighbors
						if (i != currentnode && visited[i] == false && graph[currentnode][i] != -1) { // if node not current, unvisited, and has a connection
							if (vdist[0][currentnode] + graph[currentnode][i] < vdist[0][i]) {
								vdist[0][i] = vdist[0][currentnode] + graph[currentnode][i];
								vdist[1][i] = currentnode;
							}
						}
					}
					visited[currentnode] = true; // set to visited
				}
				if (vdist[0][node2] >= INT_MAX) {
					cout << "no path" << endl;
				}
				else { // print out the data
					cout << "Length: " << vdist[0][node2] << endl;
					int point = node2;
					cout << "Path: ";
					while (point != -1) {
						char c = 'a';
						cout << (char)(c + point) << "<-";
						point = vdist[1][point];
					}
					cout << endl;
				}
			}
			else {
				cout << "node doesn't exist" << endl;
			}
		}
		else if (strcmp(input, "PRINT") == 0) { // printadjacencytable
			for (int i = 0; i < 20; i++) {
		                for (int j = 0; j < 20; j++) {
        	                	cout << graph[j][i] << " ";
				}
				cout << endl;
       			 }

		}
		else if (strcmp(input, "QUIT") == 0) { // quit
			return 0;
		}
	}
}
