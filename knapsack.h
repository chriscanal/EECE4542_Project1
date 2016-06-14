// Knapsack class
// Version f08.1
#include <iostream>
#include "item.h"
#include "bound.h"

using namespace std;

class knapsack
{
public:
        knapsack(ifstream &fin);
        knapsack(knapsack &);
        int getCost(int) const;
        int getValue(int) const;
        int getCost() const;
        int getValue() const;
        int getNumObjects() const;
        int getCostLimit() const;
        void printSolution();
        void select(int);
        void unSelect(int);
        bool isSelected(int) const;
        vector<bool> getSelected();
        vector<Item> getItems();
        void setItems(vector<Item> items);
        Bound bound();
        Bound bound(Bound &b, bool upperBound);
        void sortItemsByIndicies();

private:
        int numObjects;
        int costLimit;
        vector<Item> items;
        // vector<int> value;
        // vector<int> cost;
        // vector<bool> selected;
        int totalValue;
        int totalCost;
        void quickSort();
        void quickSortHelper(int left, int right);
};

knapsack::knapsack(ifstream &fin)
// Construct a new knapsack instance using the data in fin.
{
        int n, b, j, v, c;

        fin >> n; // read the number of objects
        fin >> b; // read the cost limit

        numObjects = n;
        costLimit = b;

        items.resize(n);
        //value.resize(n);
        //cost.resize(n);
        //selected.resize(n);

        for (int i = 0; i < n; i++)
        {
                fin >> j >> v >> c;
                items[j].setValue(v);
                items[j].setCost(c);
                items[j].unSelect();
                // value[j] = v;
                // cost[j] = c;
                // unSelect(j);
        }

        totalValue = 0;
        totalCost = 0;
}

vector<bool> knapsack::getSelected()
{
    vector<bool> selectedVector;
    for (int i = 0 ; i < numObjects ; i++)
    {
        selectedVector.push_back(items[i].isSelected());
    }
    return selectedVector;
}

vector<Item> knapsack::getItems()
{
    return items;
}


knapsack::knapsack( knapsack &k)
{
        int n = k.getNumObjects();

        items.resize(n);
        // value.resize(n);
        // cost.resize(n);
        // selected.resize(n);
        numObjects = k.getNumObjects();
        costLimit = k.getCostLimit();

        totalCost = 0;
        totalValue = 0;

        items = k.getItems();
}


int knapsack::getNumObjects() const
{
        return numObjects;
}

int knapsack::getCostLimit() const
{
        return costLimit;
}


int knapsack::getValue(int i) const
// Return the value of the ith object.
{
        if (i < 0 || i >= getNumObjects())
                throw rangeError("Bad value in knapsack::getValue");

        return items[i].getValue();
}

int knapsack::getCost(int i) const
// Return the cost of the ith object.
{
        if (i < 0 || i >= getNumObjects())
                throw rangeError("Bad value in knapsack::getCost");

        return items[i].getCost();
}

int knapsack::getCost() const
// Return the cost of the selected objects.
{
        return totalCost;
}

int knapsack::getValue() const
// Return the value of the selected objects.
{
        return totalValue;
}

ostream &operator<<(ostream &ostr, const knapsack &k)
// Print all information about the knapsack.
                {
                cout << "------------------------------------------------" << endl;
                cout << "Num objects: " << k.getNumObjects() << " Cost Limit: " << k.getCostLimit() << endl;

                int totalValue = 0;
                int totalCost = 0;

                for (int i = 0; i < k.getNumObjects(); i++)
                {
                        totalValue += k.getValue(i);
                        totalCost += k.getCost(i);
                }

                cout << "Total value: " << totalValue << endl;
                cout << "Total cost: " << totalCost << endl << endl;

                for (int i = 0; i < k.getNumObjects(); i++)
                        cout << i << "  " << k.getValue(i) << " " << k.getCost(i) << endl;

                cout << endl;

                return ostr;
        }

        void knapsack::printSolution()
// Prints out the solution.
                {
                cout << "------------------------------------------------" << endl;
                cout << "Cost Limit: " << getCostLimit() << endl;
                cout << "Total value: " << getValue() << endl;
                cout << "Total cost: " << getCost() << endl << endl;

                // Print out objects in the solution
                for (int i = 0; i < getNumObjects(); i++)
                        if (isSelected(i))
                                cout << i << "  " << getValue(i) << " " << getCost(i) << endl;

                cout << endl;
        }

        ostream &operator<<(ostream &ostr, vector<bool> v)
// Overloaded output operator for vectors.
                {
                for (int i = 0; i < v.size(); i++)
                        cout << v[i] << endl;

                return ostr;
        }

        void knapsack::select(int i)
// Select object i.
                {
                if (i < 0 || i >= getNumObjects())
                        throw rangeError("Bad value in knapsack::Select");

                if (!isSelected(i))
                {
                        items[i].select();
                        totalCost = totalCost + getCost(i);
                        totalValue = totalValue + getValue(i);
                }
        }

        void knapsack::unSelect(int i)
// unSelect object i.
                {
                if (i < 0 || i >= getNumObjects())
                        throw rangeError("Bad value in knapsack::unSelect");

                if (isSelected(i))
                {
                        items[i].unSelect();
                        totalCost = totalCost - getCost(i);
                        totalValue = totalValue - getValue(i);
                }
        }

        bool knapsack::isSelected(int i) const
// Return true if object i is currently selected, and false otherwise.
                {
                if (i < 0 || i >= getNumObjects())
                        throw rangeError("Bad value in knapsack::getValue");

                return items[i].isSelected();
        }

void knapsack::setItems(vector<Item> items)
{
    this->items = items;
    numObjects = items.size();

    for (int i = 0; i < numObjects; i++)
    {
        unSelect(i);
    }

    totalCost = 0;
    totalValue = 0;
}

void knapsack::quickSortHelper(int left, int right)
{
    int i = left, j = right;
    Item tmp;
    Item pivot = items[(left + right) / 2];

    //partition
    while (i <= j)
    {
        while (items[i].getValueCostRatio() < pivot.getValueCostRatio()) //determines how many are less than pivot
            i++;

        while (items[j].getValueCostRatio() > pivot.getValueCostRatio()) //determines how many are more than pivot
            j--;

        if (i <= j)
        //checks how the list was divided around pivot, inserts in list
        {
            tmp = items[i];
            items[i] = items[j];
            items[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        quickSortHelper(left, j); //recurs on quickHelper

    if (i < right)
        quickSortHelper(i, right); //recurs on quickHelper

}

void knapsack::quickSort()
{
    int left = 0;
	int right = getNumObjects() - 1;
	int i = left, j = right;
	Item tmp;
	Item pivot = items.at((left + right) / 2);

	//partition
	while (i <= j)
	//while size of left is less than size of right
	{
		while (items.at(i).getValueCostRatio() < pivot.getValueCostRatio()) //counts strings less than pivot
			i++;

		while (items.at(j).getValueCostRatio() > pivot.getValueCostRatio()) //strings greater than pivot
			j--;

		if (i <= j)
		//if left is less than right
		{
			tmp = items.at(i);
			items.at(i) = items.at(j);
			items.at(j) = tmp;
			i++;
			j--;
		} //end of if left is less than right

	} //end of while left is less than right

	if (left < j) //if left size is less than number less than pivot
		quickSortHelper(left, j);

	if (i < right) //if right size is less than number greater than pivot
		quickSortHelper(i, right);
}

void knapsack::sortItemsByIndicies()
{
    quickSort();
}

Bound knapsack::bound()
{
    sortItemsByIndicies();

    int fractionalItemIndex = -1;
    float fractionalTotalValue;
    bool isValid;
    vector<int> permanentSet (numObjects, -1);

    for (int i = 0; i < numObjects; i++)
    {
        unSelect(i);
    }

    for (int i = 0; i < numObjects; i++)
    {
        if (totalCost + getCost(i) <= costLimit)
        {
            select(i);
        }
        else
        {
            if (totalCost < costLimit)
            {
                fractionalItemIndex = i;
                fractionalTotalValue = (float)totalValue +  (float)((costLimit - totalCost) / getCost(i)) * (float)getValue(i);
                select(i);
                break;
            }
        }
    }

    if (fractionalItemIndex == -1)
    {
        fractionalTotalValue = (float)totalCost;
    }

    isValid = fractionalTotalValue <= (float)costLimit;

    return Bound(fractionalItemIndex, fractionalTotalValue, isValid, permanentSet);
}

Bound knapsack::bound(Bound &b, bool isUpperBound)
{
    int fractionalItemIndex = -1;
    float fractionalTotalValue;
    bool isValid;

    vector<int> permanentSet (b.getPermanentSet()); // get from Bound b
    int oldFractionalItemIndex = b.getFractionalItemIndex(); // get from Bound b, check if it equals to numObjects?

    permanentSet[oldFractionalItemIndex] = (isUpperBound)? 1: 0;

    for (int i = 0; i < numObjects; i++)
    {
        if (permanentSet[i] == 1)
        {
            select(i);
        }
        else
        {
            unSelect(i);
        }
    }

    for (int i = 0; i < numObjects; i++)
    {
        if (permanentSet[i] == -1)
        {
            if (totalCost + getCost(i) <= costLimit)
            {
                select(i);
            }
            else
            {
                if (totalCost < costLimit)
                {
                    fractionalItemIndex = i;
                    fractionalTotalValue = (float)totalValue +  (float)((costLimit - totalCost) / getCost(i)) * (float)getValue(i);
                    select(i);
                    break;
                }
            }
        }
    }

    if (fractionalItemIndex == -1)
    {
        fractionalTotalValue = (float)totalCost;
    }

    isValid = fractionalTotalValue <= (float)costLimit;

    return Bound(fractionalItemIndex, fractionalTotalValue, isValid, permanentSet);
}
