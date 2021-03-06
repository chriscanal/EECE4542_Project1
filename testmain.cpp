// main.cpp
// Advanced Algorithms Project 1               Chris Canal
//                                             canal.c@husky.neu.edu
//                                             Kenny Jean-Baptiste
//                                             jean-baptiste.ke@husky.neu.edu
//
// Project 1b: Solving knapsack using exhaustive search
//
// Code to read graph instances from a file.  Uses the Boost Graph Library (BGL).

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <fstream>
//#include <limts>

#include <boost/graph/adjacency_list.hpp>

#define LargeValue 99999999

using namespace std;
using namespace boost;

int const NONE = -1;  // Used to represent a node that does not exist

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;
typedef Graph::edge_iterator edge_iterator;
typedef Graph::vertex_iterator vertex_iterator;
typedef Graph::adjacency_iterator adj_iterator;

struct VertexProperties
{
	pair<int,int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred;
	bool visited;
	bool marked;
	int weight;
	int color;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

int initializeGraph(Graph &g, ifstream &fin)
// Initialize g using data from fin.
{
	int color;
	int n, e;
	int j,k;

	fin >> color;
	fin >> n >> e;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
		v = add_vertex(g);

	for (int i = 0; i < e; i++)
	{
		fin >> j >> k;
		add_edge(j,k,g); // Assumes vertex list is type vecS
	}
	return color;
}

void setNodeWeights(Graph &g, int w)
// Set all node weights to w.
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].weight = w;
	}
}


int exhaustiveColoring(Graph &g, int numColors, int seconds)
{
	std::cout << "\nClock time: " << clock() << std::endl;
	clock_t beginTime,currentTime;
	beginTime = clock();
	float diff;
	float timePassed = 0;
	bool noMoreColoringCombinations = false;
	int numConflicts;
	int vertexCounter;
	bool foundPlace;
	int numVertices = num_vertices(g);
	int index;
	int minConflicts = -1;

	vector <int> colorCombination(numVertices, 0);
	vector <int> bestColorCombination(numVertices, 0);


	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);

	while (!noMoreColoringCombinations && seconds > timePassed) {
		vertexCounter = 0;
		numConflicts = 0;
		// Loop over all nodes in the graph

		for (vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
		{

			g[*vItr].color = colorCombination[vertexCounter];
			vertexCounter++;
			//cout << "\nThe color of the " << vertexCounter << " node is " << g[*vItr].color;
		}
		//cout <<"\n";

		// Loop over all edges in the graph
		for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
		{
			// Returns the target vertex of edge e.
			Graph::vertex_descriptor targetNode = target(*eItr, g);
			Graph::vertex_descriptor sourceNode = source(*eItr, g);

			if (g[targetNode].color == g[sourceNode].color)
			{
				numConflicts++;
			}
		}

		if (minConflicts > numConflicts || minConflicts == -1)
		{
			minConflicts = numConflicts;
			bestColorCombination = colorCombination;
		}

		index = 0;
		foundPlace = false;
		while (!foundPlace)
		{
			if (colorCombination[index] == numColors-1)
			{
				colorCombination[index] = 0;
				if (index == numVertices - 1)
				{
					noMoreColoringCombinations = true;
					break;
				}
				else
				{
					index++;
				}
			}
			else
			{
				colorCombination[index]++;
				foundPlace = true;
			}
		}

		// checks time
		currentTime = clock();
		diff = ((float)currentTime-(float)beginTime);
		timePassed = (diff / CLOCKS_PER_SEC);
		//cout << "\ntime passed: " << timePassed << endl;
	}
	vertexCounter = 0;
	for (vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].color = bestColorCombination[vertexCounter];
		vertexCounter++;
	}
	return minConflicts;
}

void writeOutToFile(Graph &g, int conflicts, std::string inputFileName)
{
	std::string fileName = inputFileName+".output";
	ofstream myfile;
    myfile.open (fileName);

	myfile << "Total conflicts : " << conflicts << endl;

	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	// Print out objects in the solution
	for (vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		myfile << g[*vItr].color << endl;
	}

	myfile << endl;
    myfile.close();
}

int main()
{
	char x;
	ifstream fin;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.
	vector<std::string> s;
	s.push_back("color12-3");
	s.push_back("color12-4");
	s.push_back("color24-4");
	s.push_back("color24-5");
	s.push_back("color48-5");
	s.push_back("color48-6");
	s.push_back("color96-6");
	s.push_back("color96-7");
	s.push_back("color192-6");
	s.push_back("color192-7");
	s.push_back("color192-8");

	int conflicts;
	int colors;

	for (int i = 0 ; i < s.size() ; i++)
	{
		fileName = "color/"+s[i]+".input";

		//cout << "Enter filename" << endl;
		//cin >> fileName;

		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}

		try
		{
			cout << "Reading graph" << endl;
			Graph g;
			colors = initializeGraph(g,fin);

			cout << "Num nodes: " << num_vertices(g) << endl;
			cout << "Num edges: " << num_edges(g) << endl;

            //TEST CODE BEGIN
            vector< Graph::vertex_descriptor > *a;
            int left = 0;
            int right = 10;
            int i = left, j = right;
            Graph::vertex_descriptor tmp;
            Graph::vertex_descriptor pivot = a->at((left + right) / 2);
            std::cout << typeid(a).name() << '\n';

            //TEST CODE END
			conflicts = exhaustiveColoring(g,colors,600);
			writeOutToFile(g, conflicts, s[i]);
			cout << endl;

			// cout << g;
		}
		catch (int e)
		{
			cout << "An exception occurred. Exception Nr. " << e << '\n';
		}
		fin.close();
	}


}
