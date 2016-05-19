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
			if (sack.isSelected(i)) {
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
		//cout<< "\nTime Passed: " << timePassed << " seconds";
	}
	for (int i = 0; i < selectedObj.size(); i++)
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
	cout<< "\nTime Passed: " << timePassed << " seconds";
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

void quickHelper(vector< Item > *a, int left, int right)
//helper for recursion in quicksort
{
	int i = left, j = right;
	item tmp;
	item pivot = a->at((left + right) / 2);

	//partition
	while (i <= j)
	{
		while (a->at(i).getValueCostRatio() < pivot.getValueCostRatio()) //determines how many are less than pivot
			i++;

		while (a->at(j).getValueCostRatio() > pivot.getValueCostRatio()) //determines how many are more than pivot
			j--;

		if (i <= j)
		//checks how the list was divided around pivot, inserts in list
		{
			tmp = a->at(i);
			a->at(i) = a->at(j);
			a->at(j) = tmp;
			i++;
			j--;
		}
	}

	if (left < j)
		quickHelper(a, left, j); //recurs on quickHelper

	if (i < right)
		quickHelper(a, i, right); //recurs on quickHelper

} //end of quick helper

void quickSort(knapsack &sacky)
//quicksort function
{
	int left = 0;
	int right = sacky.getNumObjects()() - 1;
	int i = left, j = right;
	item tmp;
	vector< Item > itemVector(sacky.getItems())
	item pivot = itemVector.at((left + right) / 2);

	//partition
	while (i <= j)
	//while size of left is less than size of right
	{
		while (itemVector.at(i).getValueCostRatio() < pivot.getValueCostRatio()) //counts strings less than pivot
			i++;

		while (itemVector.at(j).getValueCostRatio() > pivot.getValueCostRatio()) //strings greater than pivot
			j--;

		if (i <= j)
		//if left is less than right
		{
			tmp = itemVector.at(i);
			itemVector.at(i) = itemVector.at(j);
			itemVector.at(j) = tmp;
			i++;
			j--;

		} //end of if left is less than right

	} //end of while left is less than right

	if (left < j) //if left size is less than number less than pivot
		quickHelper(&itemVector, left, j);

	if (i < right) //if right size is less than number greater than pivot
		quickHelper(&itemVector, i, right);


	sacky.setItems(itemVector);
} //end of quicksort

void greedyAlgorithm(knapsack &k)
{
	quickSort(k);
	for (int i = 0 ; i < k.getNumObjects() ; i++)
	{
		if (k.getCostLimit() >= k.getCost()+k.getCost(i))
		{
			k.select(i);
		}
	}
}

void printSack(knapsack theSmackSack)
{
	cout << "------------------------------------------------" << endl;

	cout << "Total value: " << theSmackSack.getValue() << endl;
	cout << "Total cost: " << theSmackSack.getCost() << endl << endl;

	// Print out objects in the solution
	for (int i = 0; i < theSmackSack.getNumObjects(); i++)
	{
		cout << i << "Value: " << theSmackSack.getValue(i) << "\tCost: " << theSmackSack.getCost(i) << endl;
	}

	cout << endl;
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

	for (int i = 0; i < s.size(); i++)
	{
		cout << "Enter filename" << endl;
		cin >> fileName;
		//fileName = s[i];
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

			cout << "Printing current Knapsack" << endl;
			printSack(k);

			cout << "Printing sorted Knapsack" << endl;
			quickSort(k);
			printSack(k);

			cout << "Printing final choice Knapsack" << endl;
			greedyAlgorithm(k);
			k.printSolution();


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
