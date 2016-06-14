// Bound class

using namespace std;

class Bound
{
private:
    vector<int> includedIndicies;
    vector<int> nonIncludedIndicies;
    int fractionalItemIndex;
    float fractionalTotalValue;
    bool isValid;
    vector<int> permanentSet;

public:
    Bound(vector<int> &includedIndicies, vector<int> &nonIncludedIndicies,
        int fractionalItemIndex, float fractionalTotalValue, bool isValid,
        vector<int> &permanentSet);

    boolean fathomed() const;
    void setFractionalItem(int status);
    vector<int> getPermanentSet();
    int getFractionalItemIndex();
    float getFractionalItemValue();
};

Bound::Bound(vector<int> &includedIndicies, vector<int> &nonIncludedIndicies,
    int fractionalItemIndex, float fractionalTotalValue, bool isValid,
    vector<int> &permanentSet)
{
    this->includedIndicies = includedIndicies;
    this->nonIncludedIndicies = nonIncludedIndicies;
    this->fractionalItemIndex = fractionalItemIndex;
    this->fractionalTotalValue = fractionalTotalValue;
    this->isValid = isValid;
    this->permanentSet = permanentSet;
}

boolean Bound::fathomed() const
{

}

void Bound::setFractionalItem(int status)
{

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
