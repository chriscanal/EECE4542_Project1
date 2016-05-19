// Item class

using namespace std;

class Item
{
private:
    int value;
    int cost;
    bool selected;
public:
    Item(int value, int cost, bool selected);
    int getCost() const;
    int getValue() const;
    void select();
    void unSelect();
    bool isSelected() const;
    float getValueCostRatio() const;
}

Item::Item(int value, int cost, bool selected)
{
    this->value = value;
    this->cost = cost;
    this->selected = selected;
}

int Item::Item getValue() const
{
    return value;
}

int Item::Item getCost() const
{
    return cost;
}

void Item::Item select()
{
    if (!selected)
    {
        selected[i] = true;
    }
}

void Item::Item unSelect()
{
    if (selected)
    {
        selected[i] = false;
    }
}

bool Item::Item isSelected() const
{
    return selected;
}

float Item::Item getValueCostRatio() const
{
    return (float)value / (float)cost;
}
