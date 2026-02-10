#include "pizza.hpp"

Pizza::Pizza(std::string name, int weight, float price)
    : Dish(name, weight, price)
{
}

float Pizza::GetFullPrice()
{
    return _dough == thin ? this->GetPrice() * 1.2 : this->GetPrice() * 1.4;
}

float Pizza::GetInfo()
{
    return
}
