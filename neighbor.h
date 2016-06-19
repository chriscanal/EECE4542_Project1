// Neighbor class

using namespace std;

class Neighbor
{
private:
    int value;
    vector<int> indicies;

public:
    Neighbor();
    Neighbor(int value, vector<int> indicies);
    int getValue() const;
    vector<int> getIndicies() const;
};
Neighbor::Neighbor()
{
}

Neighbor::Neighbor(int value, vector<int> indicies)
{
    this->value = value;
    this->indicies = indicies;
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
