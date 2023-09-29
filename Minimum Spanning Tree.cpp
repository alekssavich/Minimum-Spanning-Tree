//Program Name: Minimum Spanning Tree
//Programmer Name: Aleks Savich
//Description:Program will determine the minimum spanning tree of a complete tree from an input file and determine the weight.

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include <queue>
# define INF 0x3f3f3f3f
using namespace std;

typedef pair<int, int> iPair;

class AdjacencyList {
	int V;    // No. of vertices
	list< pair<int, int> >* adj; // creates a list pair called adj
public:
	AdjacencyList(int V);  // Constructor
	void addEdge(int u, int v, int w); // function to add an edge to AdjacencyList
	void primMST(int a, int b, int c); //function for prims minimum spanning tree
	void shortestPath(int a, int b); // creates shortest path using Dijkstras algorithm
};

// Pre-condition: integer v which is number of vertices
// Post-condition: this pointer to V and a new list called adj
AdjacencyList::AdjacencyList(int V) { // constructor
	this->V = V;
	adj = new list<iPair>[V];
}

// Pre-condition: integer u which is vertex 1, integer v ehich is vertex 2, and weight which is weight of edge between u and v
// Post-condition: make two pairs, (v,w) and (u,w)
void AdjacencyList::addEdge(int u, int v, int w) { // creates edge between two vertices with a weight
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

// Pre-condition: int a,b,c and char d
// Post-condition: A MST is created using a priority queue and the total weight of that MST
void AdjacencyList::primMST(int a, int b, int c) // prims minimum spanning tree
{
	int totalWeight = 0;
	priority_queue< iPair, vector <iPair>, greater<iPair> > pq; // creates priority queue

	int src = 0; // Taking vertex 0 as source
	// Create a vector for keys and initialize all
	// keys as infinite (INF)
	vector<int> key(V, INF); // creates vector for key
	vector<int> parent(V, -1); // To store parent array which in turn store MST
	vector<int> weightMST(V, -1);
	vector<bool> inMST(V, false); // keeps track of vertices in MST
	// Insert source itself in priority queue and initialize
	// its key as 0.
	pq.push(make_pair(0, src));
	key[src] = 0; // makes source of graph 0

	while (!pq.empty()) // loop until priority queue is empty
	{
		int u = pq.top().second; // takes first vertex from pair
		pq.pop(); // pop pq
		inMST[u] = true;  // Include vertex in MST

		// 'i' is used to get all adjacent vertices of a vertex
		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i){
			int v = (*i).first; // Get vertex of current adjacent of u
			int weight = (*i).second; // Get weight of current adjacent of u
			/* a and b are vertices that want to be edited by user */
			if (((a == u) && (b == v)) || ((a == v) && (b == u))) { // checks if vertices equal to edited vertices and adds or subtracts the weight from what user enters.
				weight += c; // c is the weight the user wants to add/subtract to the edge
			}

			if (weight <= 0) { // if the new weight is less than 0 tell user the error and return
				cout << "Error! The weight is <= 0" << endl;
				return; // return since if weight is <= 0 it cant be added
			}

			else {
				//  If v is not in MST and weight of (u,v) is smaller
				// than current key of v
				if (inMST[v] == false && key[v] > weight) {
					key[v] = weight; // Updating key of v
					pq.push(make_pair(key[v], v));// make pair
					parent[v] = u;
					weightMST[v] = weight; // keeps track of weight of MST
				}
			}
		}
	}
	
	for (int i = 1; i < V; ++i) { // Print edges of MST using parent array
		totalWeight += weightMST[i]; // adds total weight from MST
		if (i == V - 1) { // prints out to user the sum of the MST
			cout << weightMST[i] << "=";
			cout << weightMST[i] << "=";
		}

		else {
			cout << weightMST[i] << "+";
		}
	}
	cout << totalWeight << endl; // outputs final sum of MST
}

// Pre-condition: int a and int b where a is vertex 1 and b is vertex 2
// Post-condition: The shortest path(least weight) Between vertex a and b that is made using Djikstra's algorithm
void AdjacencyList::shortestPath(int a, int b) { // shortest path using Djikstars Algorithm
	int shortWeight = 100;// used to compare weights from each edge
	int shortWeightTotal = 0; // counts total weight of the shortest path
	int place = a; // keeps track of which node is being added to the shortest path and only to make comparisons including that node
	int holdPlace = 0;
	priority_queue< iPair, vector <iPair>, greater<iPair> > cq;
	vector<int> dist(V, INF);
	cq.push(make_pair(0, a));
	dist[a] = 0;
	while (!cq.empty()){
		int u = cq.top().second; // extract from priority queue
		cq.pop();

		// 'i' is used to get all adjacent vertices of a vertex 
		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i){
			// Get vertex label and weight of current adjacent 
			// of u. 
			int v = (*i).first;
			int weight = (*i).second;

			//  If there is shorted path to v through u. 
			if (((u >= a) && (u <= b)) && ((v >= a) && (v <= b))) { // will only use the range of nodes the user has specified to use. 
				if (dist[v] > dist[u] + weight)
				{
					// Updating distance of v 
					dist[v] = dist[u] + weight;
					cq.push(make_pair(dist[v], v));

					if ((dist[v] - shortWeightTotal < shortWeight) && (u == place)) {
						shortWeight = dist[v] - shortWeightTotal;
						holdPlace = v;
					}
				}
			}
		}
		place = holdPlace;
		if (shortWeight != 100) {
			shortWeightTotal += shortWeight;
			if (place == b) {
				cout << shortWeight << "=";
			}
			else {
				cout << shortWeight << "+";
			}
		}
		shortWeight = 100;
	}
	cout << shortWeightTotal << endl; // outputs total weight of shortest path to user
}

int main() {
	int V; // # of vertices in program
	int E; // # of edges in program
	int vertex; // first vertex from each line from input file
	int editVertex; // first vertex user wants to edit
	int vertex2; // second vertex from each line of input file
	int editVertex2; // second vertex user wants to edit
	int weight; // weight from each line of input file
	int editWeight; // weight user wants to edit
	int numLines = -1; // counts number of lines in file to check if empty or not
	char editChar; // command user wanst to use
	bool eExists = false; // checkif edge exists or not
	string unused; // used for getline to count lines in file
	string fileName; // input file
	string ofsFileName; // output file
	ifstream file;
	ofstream ofsFile;


	cout << "Welcome to Internet Grid Optimization Program" << endl;
	cout << "Enter in input file: ";
	cin >> fileName; // input file name
	file.open(fileName); // open input file

	if (!file.is_open()) { // if file cannot open, tell user file doesn exist
		cout << "Input file name provided does not exist";
		exit(0);
	}

	while (file.good()) { // while file has lines, keep adding one to numLines to get total number of lines in file.
		getline(file, unused);
		numLines++;
	}

	cout << "Enter in output file: ";
	cin >> ofsFileName; // input outfile name
	ofsFile.open(ofsFileName); // create and open outfile name
	ofsFile << "Welcome to Internet Grid Optimization Program" << endl;

	if (numLines == 0) { // if the number of lines is 0 in the input file, tell user file exists with no data.
		cout << "Input file exists but contains no data - program ended"; // output to user
		ofsFile << "Input file exists but contains no data - program ended"; //output to file
		file.close(); // close input file
		ofsFile.close(); // close output file
		return 0; // since no data exists, end program
	}

	file.close();
	file.open(fileName);

	file >> V;
	file >> E;

	AdjacencyList g(V);
	vector< list< pair<int, int> > > adjacencyList(V + 1);

	cout << "Creating file from " << fileName << endl;

	cout << "Graph will contain " << V << " verticies and " << E << " edges" << endl;

	cout << "Verticies: ";
	for (int i = 0; i < V; i++) {
		cout << i;
		if (i != V - 1) {
			cout << ",";
		}
	}

	cout << endl;

	for (int i = 0; i < E; i++) { // takes each line of input file and sets them to the appropiate variable
		file >> vertex;
		file >> vertex2;
		file >> weight;
		cout << "Vertex 1: " << vertex;
		ofsFile << "Vertex 1: " << vertex;

		cout << "    Vertex 2: " << vertex2;
		ofsFile << "    Vertex 2: " << vertex2;

		cout << "    Weight: " << weight << " ";
		ofsFile << "    Weight: " << weight << " ";

		if ((vertex >= V) || (vertex < 0)) { // If first vertex is not within range of available verticies
			cout << "Error! Invalid vertex: " << vertex << " is not a valid vertex" << endl;; // tell user vertex is not valid
			ofsFile << "Error! Invalid vertex: " << vertex << " is not a valid vertex" << endl; // tell user vertex is not valid
			E--; // decrease edges by one since an edge is not created.
		}

		else if ((vertex2 >= V) || (vertex2 < 0)) { // If second vertex is not within range of available verticies
			cout << "Error! Invalid vertex: " << vertex2 << " is not a valid vertex " << endl;; // tell user vertex is not valid
			ofsFile << "Error! Invalid vertex: " << vertex2 << " is not a valid vertex" << endl; // tell user vertex is not valid
			E--; // decrease edges by one since an edge is not created.
		}

		else if (weight <= 0) {
			cout << "Error! Invalid weight(<=0): " << weight << " is not a valid weight" << endl;
			ofsFile << "Error! Invalid weight(<=0): " << weight << " is not a valid weight" << endl;
			E--; // decrease edges by one since an edge is not created.
		}

		else { // output on screen the two verticies and the weight
			cout << endl;
			ofsFile << endl;
			g.addEdge(vertex, vertex2, weight); // add edge in tree
			adjacencyList[vertex].push_back(make_pair(vertex2, weight)); // add to the adjacency list
		}
	}

	ofsFile << "File has " << V << " vertices and " << E << " edges." << endl;

	for (int i = 0; i < adjacencyList.size() - 1; ++i) { // prints adjacency list

		printf("adj[%d]", i);

		list< pair<int, int> >::iterator itr = adjacencyList[i].begin();

		while (itr != adjacencyList[i].end()) { // while adjacency list is not at the end, out output adjacency list

			printf(" -> [%d,%d]", (*itr).first, (*itr).second);
			++itr;
		}
		printf("\n");
	}

	g.primMST(0, 0, 0);
	file.close(); //close input file

	cout << "Enter in the edit you would like to make or X if you would like to exit program: ";
	ofsFile << "Enter in the edit you would like to make or X if you would like to exit program: ";
	cin >> editChar;
	while (editChar != 'X') {
		if (editChar == 'E') { // creates new edge in tree only if edge doesnt currently exist
			cout << "Vertex 1: ";
			ofsFile << "Vertex 1: ";
			cin >> editVertex; // enter in the vertices and the weight you would like to edit
			while ((editVertex < 0) || (editVertex > V)) {
				cout << "Invalid Vertex. Please enter in a valid vertex: ";
				ofsFile << "Invalid Vertex. Please enter in a valid vertex: ";
				cin >> editVertex;
			}

			cout << "Vertex 2: ";
			ofsFile << "Vertex 2: ";
			cin >> editVertex2;
			while ((editVertex2 < 0) || (editVertex2 > V) || (editVertex == editVertex2)) {
				cout << "Invalid Vertex. Please enter in a valid vertex: ";
				ofsFile << "Invalid Vertex. Please enter in a valid vertex: ";
				cin >> editVertex2;
			}

			cout << "Weight: ";
			ofsFile << "Weight: ";
			cin >> editWeight;
			while (editWeight < 0) {
				cout << "Invalid Weight. Please enter in a valid Weight ";
				ofsFile << "Invalid Weight. Please enter in a valid Weight ";
				cin >> editVertex;
			}

			file.open(fileName); // open input file and getline once
			getline(file, unused);
			for (int i = 0; i < E; i++) { // goes through each line of input file to check if the vertices that wante to be edited already exist 
				file >> vertex;
				file >> vertex2;
				file >> weight;
				if (((editVertex == vertex) && (editVertex2 == vertex2)) || ((editVertex == vertex2) && (editVertex2 == vertex))) {
					cout << "The edge you are trying to add already exists" << endl;
					ofsFile << "The edge you are trying to add already exists" << endl;
					eExists = true;
					i = E;
				}
			}
			if (eExists == false) { // if the edge does not exist, then create a new edge
				g.addEdge(editVertex, editVertex2, editWeight); // calls add edge function with new vertices and new weights as parameters
				adjacencyList[editVertex].push_back(make_pair(editVertex2, editWeight)); // add to the adjacency list
				g.primMST(0, 0, 0);
				for (int i = 0; i < adjacencyList.size() - 1; ++i) { // prints adjacency list

					printf("adj[%d]", i);

					list< pair<int, int> >::iterator itr = adjacencyList[i].begin();

					while (itr != adjacencyList[i].end()) { // while adjacency list is not at the end, out output adjacency list

					printf(" -> [%d,%d]", (*itr).first, (*itr).second);
						++itr;
					}
					printf("\n");
				}
			}
			file.close(); // close input file
		}

		else if (editChar == 'I') { // increase existing edge by a certain weight

			cout << "Vertex 1: ";
			ofsFile << "Vertex 1: ";
			cin >> editVertex;
			while ((editVertex < 0) || (editVertex > V)) {
				cout << "Invalid Vertex. Please enter in a valid vertex ";
				ofsFile << "Invalid Vertex. Please enter in a valid vertex ";
				cin >> editVertex;
			}

			cout << "Vertex 2: ";
			cin >> editVertex2;
			while ((editVertex2 < 0) || (editVertex2 > V) || (editVertex == editVertex2)) {
				cout << "Invalid Vertex. Please enter in a valid vertex ";
				ofsFile << "Invalid Vertex. Please enter in a valid vertex ";
				cin >> editVertex2;
			}

			cout << "Weight: ";
			ofsFile << "Weight: ";
			cin >> editWeight;
			while (editWeight < 0) {
				cout << "Invalid Weight. Please enter in a valid Weight ";
				ofsFile << "Invalid Weight. Please enter in a valid Weight ";
				cin >> editVertex;
			}

			file.open(fileName);
			getline(file, unused);
			for (int i = 0; i < E; i++) {
				file >> vertex;
				file >> vertex2;
				file >> weight;
				if (((editVertex == vertex) && (editVertex2 == vertex2)) || ((editVertex == vertex2) && (editVertex2 == vertex))) {
					eExists = true;
					g.primMST(editVertex, editVertex2, editWeight);
				}
			}
			if (eExists == false) { // if edge does not exist, tell user the edge does not exist
				cout << "The edge you are trying to edit does not exist" << endl;
				ofsFile << "The edge you are trying to edit does not exist" << endl;
			}
			file.close(); // file close
		}

		else if (editChar == 'D') { // Command D is to decrease the weight of an existing edge
			cout << "Vertex 1: ";
			ofsFile << "Vertex 1: ";
			cin >> editVertex;
			while ((editVertex < 0) || (editVertex > V)) {
				cout << "Invalid Vertex. Please enter in a valid vertex ";
				ofsFile << "Invalid Vertex. Please enter in a valid vertex ";
				cin >> editVertex;
			}

			cout << "Vertex 2: ";
			ofsFile << "Vertex 2: ";
			cin >> editVertex2;
			while ((editVertex2 < 0) || (editVertex2 > V) || (editVertex == editVertex2)) {
				cout << "Invalid Vertex. Please enter in a valid vertex ";
				ofsFile << "Invalid Vertex. Please enter in a valid vertex ";
				cin >> editVertex2;
			}

			cout << "Weight: ";
			cin >> editWeight;
			while (editWeight < 0) {
				cout << "Invalid Weight. Please enter in a valid Weight ";
				ofsFile << "Invalid Weight. Please enter in a valid Weight ";
				cin >> editVertex;
			}

			file.open(fileName);
			getline(file, unused);
			for (int i = 0; i < E; i++) {
				file >> vertex;
				file >> vertex2;
				file >> weight;
				if (((editVertex == vertex) && (editVertex2 == vertex2)) || ((editVertex == vertex2) && (editVertex2 == vertex))) {
					eExists = true;
					editWeight *= -1;
					g.primMST(editVertex, editVertex2, editWeight); // call prims MST with new vertices and weight parameters
				}
			}
			if (eExists == false) { // if edge does not exist, tell user edge does not exist
				cout << "The edge you are trying to edit does not exist" << endl;
				ofsFile << "The edge you are trying to edit does not exist" << endl;
			}
			file.close(); // files close
		}

		else if (editChar == 'S') { // If S is entered print the shortest path from vertex one to vertex 2
			cin >> editVertex;
			cin >> editVertex2;
			g.shortestPath(editVertex, editVertex2);
		}

		else {
			cout << "Command you have entered is invalid: " << editChar << endl;
			ofsFile << "Command you have entered is invalid: " << editChar << endl;
		}
		cout << "Enter in the edit you would like to make or X if you would like to exit program: ";
		ofsFile << "Enter in the edit you would like to make or X if you would like to exit program: ";
		cin >> editChar;
	}
	return 0;
}
