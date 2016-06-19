// Neighbor class

using namespace std;

class Neighbor
{
private:
    int removedItemIndex;
    int value;
    vecotr<int> indicies;

public:
    Neighbor(int removedItemIndex, int value, vector<int> indicies);
    int getRemovedItemIndex() const;
    int getValue() const;
    vector<int> getIndicies() const;
};

Neighbor::Neighbor(int removedItemIndex, int value, vector<int> indicies)
{
    this->removedItemIndex = removedItemIndex;
    this->value = value;
    this->indicies = indicies;
}

int Neighbor::getRemovedItemIndex() const
{
    return removedItemIndex;
}

int Neighbor::getValue() const
{
    return value;
}

vector<int> Neighbor::getIndicies() const
{
    return indicies;
}

bool operator<(const Neighbor &n1, const Neighbor &n2)
{
    return n1.getValue() < n2.getValue();
}

bool operator>(const Neighbor &n1, const Neighbor &n2)
{
   return n1.getValue() > n2.getValue();
}

bool operator==(const Neighbor &n1, const Neighbor &n2)
{
   return n1.getValue() == n2.getValue();
}

bool operator<=(const Neighbor &n1, const Neighbor &n2)
{
   return n1.getValue() <= n2.getValue();
}

bool operator>=(const Neighbor &n1, const Neighbor &n2)
{
   return n1.getValue() >= n2.getValue();
}
