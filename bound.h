// Bound class

using namespace std;

class Bound
{
private:
    int value;
    int cost;
    bool selected;
public:
    Item();
    Item(int value, int cost, bool selected);
    int getCost() const;
    int getValue() const;
    void select();
    void unSelect();
    bool isSelected() const;
    float getValueCostRatio() const;
    void setValue(int newValue);
    void setCost(int newCost);

    //operator Overloaded
    void operator=(const Item &newItem)
    {
        value = newItem.getValue();
        cost = newItem.getCost();
        selected = newItem.isSelected();
    }
};

Item::Item()
{
    this->value = 0;
    this->cost = 0;
    this->selected = false;
}

Item::Item(int value, int cost, bool selected)
{
    this->value = value;
    this->cost = cost;
    this->selected = selected;
}

int Item::getValue() const
{
    return value;
}

int Item::getCost() const
{
    return cost;
}

void Item::select()
{
    if (!selected)
    {
        selected = true;
    }
}

void Item::unSelect()
{
    if (selected)
    {
        selected = false;
    }
}

bool Item::isSelected() const
{
    return selected;
}

float Item::getValueCostRatio() const
{
    return (float)value / (float)cost;
}

void Item::setValue(int newValue)
{
    value = newValue;
}

void Item::setCost(int newCost)
{
    cost = newCost;
}
