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

void greedyKnapsack(knapsack &sack)
{
	
}

void exhaustiveKnapsack(knapsack &sack, int seconds)
{
	std::cout << "\nClock time: " << clock() << std::endl;
    clock_t beginTime,currentTime;
	beginTime = clock();
	float diff;
	float timePassed;
	bool noMoreKnapsackSets = false;
	vector <bool> selectedObj;
	int score = 0;

	while (!noMoreKnapsackSets && seconds > timePassed)
	{
		if (score < sack.getValue() && sack.getCost() <= sack.getCostLimit() )
		{
			score = sack.getValue();
			selectedObj = sack.getSelected();
		}

		noMoreKnapsackSets = !successfulIncrementKnapsackSet(sack);

		currentTime = clock();
		diff = ((float)currentTime-(float)beginTime);
		timePassed = (diff / CLOCKS_PER_SEC);
		//cout<< "\nTime Passed: " << timePassed << " seconds";
	}

	setKnapsackSelectedSet(sack, selectedObj);

	cout<< "\nTime Passed: " << timePassed << " seconds";
}

//
void resetKnapsackSetSelection(knapsack &sack)
{
	for (int i = 0; i < sack.getNumObjects(); i++)
	{
		sack.unSelect(i);
	}
}

//Returns True on Success
bool successfulIncrementKnapsackSet(knapsack &sack)
{
	bool foundPlace = false;
	int index = 0;
	while (!foundPlace)
	{
		if (sack.isSelected(index))
		{
			sack.unSelect(index);
			if (index == sack.getNumObjects() - 1)
			{
				return foundPlace;
			}
			else
			{
				index++;
			}
		}
		else
		{
			sack.select(index);
			foundPlace = true;
		}
	}
	return foundPlace;
}

//sets Knapsack Selection to select
void setKnapsackSelectedSet(knapsack &sack, vector<bool> &select)
{
	for (int i = 0; i < select.size() ; i++)
	{
		if (select[i])
		{
			sack.select(i);
		}
		else
		{
			sack.unSelect(i);
		}
	}
}

void writeOutToFile(knapsack &sack)
{
	std::string fileName = "knapsack"+std::to_string(sack.getNumObjects())+".output";
	ofstream myfile;
    myfile.open (fileName);

	myfile << "Total value: " << sack.getValue() << endl;
	myfile << "Total cost: " << sack.getCost() << endl << endl;

	// Print out objects in the solution
	for (int i = 0; i < sack.getNumObjects(); i++)
			if (sack.isSelected(i))
					myfile << i << "  " << sack.getValue(i) << " " << sack.getCost(i) << endl;

	myfile << endl;
    myfile.close();
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

	//cout << "Enter filename" << endl;
	//cin >> fileName;
	vector<std::string> s;
	s.push_back("knapsack/knapsack8.input");
	s.push_back("knapsack/knapsack12.input");
	s.push_back("knapsack/knapsack16.input");
	s.push_back("knapsack/knapsack20.input");
	s.push_back("knapsack/knapsack28.input");
	s.push_back("knapsack/knapsack32.input");
	s.push_back("knapsack/knapsack48.input");
	s.push_back("knapsack/knapsack64.input");
	s.push_back("knapsack/knapsack128.input");
	s.push_back("knapsack/knapsack256.input");
	s.push_back("knapsack/knapsack512.input");
	s.push_back("knapsack/knapsack1024.input");
	for (int i = 0 ; i < s.size() ; i++)
	{
		fileName = s[i];
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
			writeOutToFile(k);

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
		fin.close();

	}

}
