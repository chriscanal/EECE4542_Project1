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
    bool isFathomed = false;

public:
    Bound(vector<int> includedIndicies, int fractionalItemIndex,
        float fractionalTotalValue, int regularTotalCost, bool isValid,
        vector<int> &permanentSet);

    boolean fathomed() const;
    vector<int> getPermanentSet();
    int getFractionalItemIndex();
    float getFractionalItemValue();
    int getRegularTotalCost();
    vector<int> getIncludedIndicies();

    boolean valid() const
    {
        return isValid;
    }
};

Bound::Bound(vector<int> includedIndicies, int fractionalItemIndex,
    float fractionalTotalValue, int regularTotalCost, bool isValid,
    vector<int> &permanentSet)
{
    this->includedIndicies = includedIndicies;
    this->fractionalItemIndex = fractionalItemIndex;
    this->fractionalTotalValue = fractionalTotalValue;
    this->regularTotalCost = regularTotalCost;
    this->isValid = isValid;
    this->permanentSet = permanentSet;
    isFathomed = fractionalItemIndex == -1;
}

boolean Bound::fathomed() const
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

int Bound::getFractionalItemIndex()
{
    return fractionalItemIndex;
}

float Bound::getFractionalItemValue()
{
    return fractionalTotalValue;
}

int Bound::getRegularTotalCost()
{
    return regularTotalCost
}

bool operator<(const bound &b1, const bound &b2)
{
    b1.getFractionalItemValue() < b2.getFractionalItemValue()
}

bool operator>(const bound &b1, const bound &b2)
{
   b1.getFractionalItemValue() > b2.getFractionalItemValue()
}

bool operator==(const bound &b1, const bound &b2)
{
   b1.getFractionalItemValue() == b2.getFractionalItemValue()
}

bool operator<=(const bound &b1, const bound &b2)
{
   b1.getFractionalItemValue() <= b2.getFractionalItemValue()
}

bool operator>=(const bound &b1, const bound &b2)
{
   b1.getFractionalItemValue() >= b2.getFractionalItemValue()
}
