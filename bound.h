// Bound class

using namespace std;

class Bound
{
private:
    float value;
    int cost;
    int fractionalItemIndex;
    std::vector<int> permanentSet;
    std::vector<int> included;
public:
    Bound();

    boolean fathomed() const;
    void setFractionalItem(int status);
    void addBestItems();
    void addFractionalItem();
};

Bound::Bound()
{

}

boolean Bound::fathomed() const
{

}
void Bound::setFractionalItem(int status)
{

}
void Bound::addBestItems()
{

}
void Bound::addFractionalItem()
{

}
