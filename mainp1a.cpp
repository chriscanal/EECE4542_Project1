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
	std::cout << "\nClock time: " << clock() << std::endl;
    clock_t beginTime,currentTime;
	beginTime = clock();
	float diff;
	float timePassed;
	std::vector<bool> trueVector(sack.getNumObjects(), true);
	int i = 0;
	bool foundPlace = false;
	bool noMoreKnapsackSets = false;
	vector <bool> selectedObj(sack.getNumObjects(),false);
	int score = 0;

	while (!noMoreKnapsackSets && seconds > timePassed)
	{
		if (score < sack.getValue() && sack.getCost() <= sack.getCostLimit() )
		{
			score = sack.getValue();
			selectedObj = sack.getSelected();
		}
		foundPlace = false;
		i = 0;
		while (!foundPlace)
		{
			if (sack.isSelected(i)){
				sack.unSelect(i);
				if (i == sack.getNumObjects() - 1)
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
		currentTime = clock();
		diff = ((float)currentTime-(float)beginTime);
		timePassed = (diff / CLOCKS_PER_SEC);
		cout<< "\nTime Passed: " << timePassed << seconds;
	}
	for (int i = 0; i < selectedObj.size() ; i++)
	{
		if (selectedObj[i])
		{
			sack.select(i);
		}
		else
		{
			sack.unSelect(i);
		}
	}
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

		exhaustiveKnapsack(k, 10);

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
