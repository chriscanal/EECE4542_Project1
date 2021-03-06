// main.cpp
// Advanced Algorithms Project 1               Chris Canal
//                                             canal.c@husky.neu.edu
//                                             Kenny Jean-Baptiste
//                                             jean-baptiste.ke@husky.neu.
//
// Project 1a: Solving knapsack using exhaustive search
//


#include <string>
#include <sstream>
#include <iostream>
#include <stack>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <time.h>
#include <math.h>

#include "d_except.h"
#include "d_matrix.h"
#include "knapsack.h"
#include "neighbor.h"

using namespace std;

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
	Item tmp;
	Item pivot = a->at((left + right) / 2);

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
	int right = sacky.getNumObjects() - 1;
	int i = left, j = right;
	Item tmp;
	vector< Item > itemVector(sacky.getItems());
	Item pivot = itemVector.at((left + right) / 2);

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

Neighbor greedyKnapsack(knapsack &k)
{
	for (int i = 0 ; i < k.getNumObjects(); i++)
	{
		if (k.getCostLimit() >= k.getCost()+k.getCost(i))
		{
			k.select(i);
		}
	}

    return Neighbor(k.getValue(), k.getIndicies());
}

/*
Neighbor greedyKnapsack(knapsack &k, int j)
{
    k.unSelect(j);
	for (int i = 0 ; i < k.getNumObjects() ; i++)
	{
		if (k.getCostLimit() >= k.getCost()+k.getCost(i) && i != j)
		{
			k.select(i);
		}
	}
    Neighbor newNeighbor(j, k.getValue(), k.getIndicies());
    return newNeighbor;
}
*/

Neighbor greedyKnapsack(knapsack &k, vector<int> indicies, int j)
{
	k.setItems(indicies);
	k.unSelect(j);

	for (int i = 0; i < k.getNumObjects(); i++)
	{
		if (!k.isSelected(i) && i != j && k.getCostLimit() >= k.getCost() + k.getCost(i))
		{
			k.select(i);
		}
	}

	return Neighbor(k.getValue(), k.getIndicies());
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

void branchAndBound(knapsack &k, float maxTime)
{
	std::cout << "\nClock time: " << clock() << std::endl;
    clock_t beginTime,currentTime;
	beginTime = clock();
	float diff;
	float timePassed = 0.0;

	Bound zeroCase;
	Bound oneCase;

	std::priority_queue<Bound> boundsQue;
	Bound firstBound = k.bound();
	boundsQue.push(firstBound);

	int bestValue = 0;

	Bound bestBound;
	Bound currentBound;

	while (boundsQue.size() > 0 && timePassed < maxTime)
	{
		currentBound = boundsQue.top();
		boundsQue.pop();

		if (currentBound.fathomed() == false)
		{



			zeroCase = k.bound(currentBound, false);
			oneCase = k.bound(currentBound, true);

			if (zeroCase.getRegularTotalValue() > bestValue)
			{
				bestValue = zeroCase.getRegularTotalValue();
				bestBound = zeroCase;
			}
			if (oneCase.getRegularTotalValue() > bestValue)
			{
				bestValue = oneCase.getRegularTotalValue();
				bestBound = oneCase;
			}

			if (zeroCase.fathomed() == false && zeroCase.getFractionalItemValue() > bestValue)
			{
				boundsQue.push(zeroCase);
			} else {
				if (zeroCase.getRegularTotalValue() > bestValue)
				{
					bestValue = zeroCase.getRegularTotalValue();
					bestBound = zeroCase;
				}
			}

			if (oneCase.fathomed() == false && oneCase.getFractionalItemValue() > bestValue)
			{
				boundsQue.push(oneCase);
			} else {
				if (oneCase.getRegularTotalValue() > bestValue)
				{
					bestValue = oneCase.getRegularTotalValue();
					bestBound = oneCase;
				}
			}
		} else {
			if (currentBound.getRegularTotalValue() > bestValue)
			{
				bestValue = currentBound.getRegularTotalValue();
				bestBound = currentBound;
			}
		}
		currentTime = clock();
		diff = ((float)currentTime-(float)beginTime);
		timePassed = (diff / CLOCKS_PER_SEC);
	}
	k.setItems(bestBound.getIncludedIndicies());
}


Neighbor bestNeighbor(knapsack &k, Neighbor &currentN)
{
    Neighbor newN;
    Neighbor bestN = currentN;

	vector<int> indicies(currentN.getIndicies());

    for (int i = 0 ; i < indicies.size() ; i++)
    {
        newN = greedyKnapsack(k, indicies, indicies[i]);

		if (newN.getValue() > bestN.getValue())
        {
            bestN = newN;
        }
    }

    return bestN;
}

void steepestDecent(knapsack &k)
{
	k.sortItemsByIndicies();
    vector<int> indicies;
    Neighbor currentN(0,indicies);

    Neighbor nextN = greedyKnapsack(k);

    while(currentN.getValue() < nextN.getValue())
    {
        cout << "This \n";
        currentN = nextN;
        nextN = bestNeighbor(k, currentN);
    }
    k.setItems(currentN.getIndicies());
}

bool contains(const vector<int> &v, int item)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == item)
		{
			return true;
		}
	}

	return false;
}

Neighbor bestNeighborTabu(knapsack &k, Neighbor &currentN, vector<int> &tabuIndicies)
{
	Neighbor newN;
    Neighbor bestN = currentN;

	vector<int> indicies(currentN.getIndicies());

	int tabuIndex = -1;

    for (int i = 0 ; i < indicies.size(); i++)
    {
		if (!contains(tabuIndicies, item))
		{
			newN = greedyKnapsack(k, indicies, indicies[i]);

			if (newN.getValue() > bestN.getValue())
	        {
	            bestN = newN;
	        }
		}
    }

	if (tabuIndex != -1)
	{
		tabuIndicies.push_back(tabuIndex);
	}

    return bestN;
}

void linKernigham(knapsack &k)
{
	k.sortItemsByIndicies();

	vector<int> tabuIndicies;
	vector<int> indicies;

	Neighbor currentN(0, indicies);

	Neighbor nextN = greedyKnapsack(k);

	while(tabuIndicies.size() < k.getNumObjects() && currentN.getValue() < nextN.getValue())
	{
		currentN = nextN;
        nextN = bestNeighbor(k, currentN);
	}

	k.setItems(currentN.getIndicies());
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
    /*
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
    */

	for (int i = 0; i < s.size(); i++)
	{
		//cout << "Enter filename" << endl;
		//cin >> fileName;
		fileName = s[i];
		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
		}

		try
		{
			cout << "Reading knapsack instance" << endl;
			knapsack k(fin);

			cout << "Printing final choice Knapsack" << endl;
			steepestDecent(k);
			k.printSolution();

			//exhaustiveKnapsack(k, 600);
			writeOutToFile(k);

			cout << endl << "Best solution" << endl;
			k.printSolution();

		}


		catch (indexRangeError &ex)
		{
			cout << ex.what() << endl;
		}
		catch (rangeError &ex)
		{
			cout << ex.what() << endl;
		}
		fin.close();

	}

}
