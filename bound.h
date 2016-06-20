// Bound class

using namespace std;

class Bound
{
private:
    int fractionalItemIndex;
    float fractionalTotalValue;
    int regularTotalCost;
    bool isValid;
    vector<int> includedIndicies;
    vector<int> permanentSet;
    bool isFathomed;
    int regularTotalValue;

public:
    Bound();
    Bound(vector<int> includedIndicies, int fractionalItemIndex,
        float fractionalTotalValue, int regularTotalValue, int regularTotalCost,
        bool isValid, vector<int> permanentSet);
    //Bound(Bound &obj);

    bool fathomed() const;
    vector<int> getPermanentSet();
    int getFractionalItemIndex() const;
    float getFractionalItemValue() const;
    int getRegularTotalCost() const;
    int getRegularTotalValue() const;
    vector<int> getIncludedIndicies();

    bool valid() const
    {
        return isValid;
    }
};

Bound::Bound(vector<int> includedIndicies, int fractionalItemIndex,
float fractionalTotalValue, int regularTotalValue, int regularTotalCost,
bool isValid, vector<int> permanentSet)
{
    this->includedIndicies = includedIndicies;
    this->fractionalItemIndex = fractionalItemIndex;
    this->fractionalTotalValue = fractionalTotalValue;
    this->regularTotalCost = regularTotalCost;
    this->regularTotalValue = regularTotalValue;
    this->isValid = isValid;
    this->permanentSet = permanentSet;
    isFathomed = fractionalItemIndex == -1;
}

Bound::Bound()
{
    isFathomed = false;
}

//copy constructor
/*
Bound::Bound(Bound & obj)
{
    fractionalItemIndex = obj.getFractionalItemIndex();
    fractionalTotalValue = obj.getFractionalItemValue();
    isValid = true;
    permanentSet = obj.getPermanentSet();
    isFathomed = false;
}
*/

bool Bound::fathomed() const
{
    return isFathomed;
}

vector<int> Bound::getPermanentSet()
{
    return permanentSet;
}

vector<int> Bound::getIncludedIndicies()
{
    return includedIndicies;
}

int Bound::getFractionalItemIndex() const
{
    return fractionalItemIndex;
}

float Bound::getFractionalItemValue() const
{
    return fractionalTotalValue;
}

int Bound::getRegularTotalCost() const
{
    return regularTotalCost;
}

int Bound::getRegularTotalValue() const
{
    return regularTotalValue;
}

bool operator<(const Bound &b1, const Bound &b2)
{
    return b1.getFractionalItemValue() < b2.getFractionalItemValue();
}

bool operator>(const Bound &b1, const Bound &b2)
{
   return b1.getFractionalItemValue() > b2.getFractionalItemValue();
}

bool operator==(const Bound &b1, const Bound &b2)
{
   return b1.getFractionalItemValue() == b2.getFractionalItemValue();
}

bool operator<=(const Bound &b1, const Bound &b2)
{
   return b1.getFractionalItemValue() <= b2.getFractionalItemValue();
}

bool operator>=(const Bound &b1, const Bound &b2)
{
   return b1.getFractionalItemValue() >= b2.getFractionalItemValue();
}
