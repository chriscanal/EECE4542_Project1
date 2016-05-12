// main.cpp
// Advanced Algorithms Project 1               Chris Canal
//                                             canal.c@husky.neu.edu
//                                             Kenny Jean-Baptiste
//                                             jean-baptiste.ke@husky.neu.
//
// Project 1a: Solving knapsack using exhaustive search
//

#include <iostream>
#include <stack>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

#include "d_except.h"
#include "d_matrix.h"
#include <boost/graph/adjacency_list.hpp>
#include "knapsack.h"

using namespace boost;
using namespace std;


void exhaustiveKnapsack(knapsack &sack,int seconds)
{
	std::vector<bool> trueVector(numObjects, true);
	int i = 0;
	bool foundPlace = false;
	bool noMoreKnapsackSets = false;
	vector <bool> selectedObj = sack.selected; // this is broken
	int score = 0;

	while (!noMoreKnapsackSets)
	{
		if (score < sack.getValue() && sack.getCost() <= getCostLimit() )
		{
			score = sack.getValue();
			selectedObj = ;//do this later
		}
		foundPlace = false;
		i = 0;
		while (!foundPlace)
		{
			if (sack.isSelected(i){
				sack.unSelect(i);
				if (i == numObjects - 1)
				{
					noMoreKnapsackSets = true;
				} else
				{
					i++;
				}
			} else {
				sack.select(i);
				foundPlace = true;
			}
		}
	}
}

void resetKnapsackSelection(knapsack &sack)
{

}

bool incrementSelection(knapsack &sack)
{
	std::vector<bool> lastCase = ;

	if lastCase == sack.selected
}

int turnOn(int i, knapsack &sack){
	if (i == sack.numObjects){
		return sack.getCost();
	} else {
		return turnOn(i+1)
	}
}

void turnOff(){

}

int main()
{
	char x;
	ifstream fin;
	stack <int> moves;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	// fileName = "knapsack16.input";

	cout << "Enter filename" << endl;
	cin >> fileName;

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		cout << "Reading knapsack instance" << endl;
		knapsack k(fin);

		exhaustiveKnapsack(k, 600);

		cout << endl << "Best solution" << endl;
		k.printSolution();

	}

	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
	catch (rangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
}
