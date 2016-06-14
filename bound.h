// Bound class

using namespace std;

class Bound
{
private:
    int fractionalItemIndex;
    float fractionalTotalValue;
    bool isValid;
    vector<int> permanentSet;
    bool isFathomed = false;

public:
    Bound(int fractionalItemIndex, float fractionalTotalValue,
        bool isValid, vector<int> &permanentSet);

    boolean fathomed() const;
    vector<int> getPermanentSet();
    int getFractionalItemIndex();
    float getFractionalItemValue();

    boolean valid() const
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

boolean Bound::fathomed() const
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
