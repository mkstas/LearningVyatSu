#pragma once

#include <string>
#include <iomanip>
#include <iostream>

class Dish
{
public:
	Dish()
		: _name("Dish")
		, _weight(100)
		, _price(10.0)
	{
	}

	Dish(std::string name)
		: _name(std::move(name))
		, _weight(200)
		, _price(20.0)
	{
	}

	Dish(std::string name, int weight, double price = 15.0)
		: _name(std::move(name))
		, _weight(weight)
		, _price(price)
	{
	}

	std::string GetName()	const { return _name; }
	int			GetWeight() const { return _weight; }
	double		GetPrice()	const { return _price; }

	virtual void DisplayInfo() = 0 {}
	virtual double GetFullPrice() = 0 {}

private:
	std::string _name;
	int			_weight;
	double		_price;
};
