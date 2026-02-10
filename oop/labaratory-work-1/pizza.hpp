#include "dish.hpp"

enum Dough
{
    thin,
    thick
};

class Pizza : Dish
{
private:
    Dough _dough = thick;

public:
    Pizza(std::string name, int weight, float price);

    float GetFullPrice() override;
    std::string GetInfo() override;

    void ChangeDough();
    void CutInSlices();
};
