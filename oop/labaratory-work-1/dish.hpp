#pragma once
#include <string>

class Dish
{
private:
    std::string _name;
    int _weight;
    float _price;

public:
    Dish(std::string name, int weight, float price)
    {
        _name = name;
        _weight = weight;
        _price = price;
    }

    std::string GetName()
    {
        return _name;
    }

    float GetPrice()
    {
        return _price;
    }

    virtual float GetFullPrice() = 0;
    virtual std::string GetInfo() = 0;
};
