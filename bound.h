// Bound class

using namespace std;

class Bound
{
private:
    int fractionalItemIndex;
    float fractionalTotalValue;
    bool isValid;
    vector<int> permanentSet;
    bool isFathomed;

public:
    Bound();
    Bound(int fractionalItemIndex, float fractionalTotalValue,
        bool isValid, vector<int> &permanentSet);
    Bound(const Bound &obj);

    bool fathomed() const;
    vector<int> getPermanentSet();
    int getFractionalItemIndex();
    float getFractionalItemValue();

    bool valid() const
    {
        return isValid;
    }
};

Bound::Bound(int fractionalItemIndex, float fractionalTotalValue,
    bool isValid, vector<int> &permanentSet)
{
    this->fractionalItemIndex = fractionalItemIndex;
    this->fractionalTotalValue = fractionalTotalValue;
    this->isValid = isValid;
    this->permanentSet = permanentSet;
    isFathomed = fractionalItemIndex == -1;
}

Bound::Bound()
{
    isFathomed = false;
}

//copy constructor
Bound(const Bound &obj)
{
    fractionalItemIndex = obj.getFractionalItemIndex();
    fractionalTotalValue = obj.getFractionalItemValue();
    isValid = true;
    permanentSet = obj.getPermanentSet();
    isFathomed = false;
}

bool Bound::fathomed() const
{
    return isFathomed;
}

vector<int> Bound::getPermanentSet()
{
    return permanentSet;
}

int Bound::getFractionalItemIndex()
{
    return fractionalItemIndex;
}

float Bound::getFractionalItemValue()
{
    return fractionalTotalValue;
}
