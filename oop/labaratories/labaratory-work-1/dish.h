#pragma once

#include <string>
#include <iomanip>
#include <iostream>

class Dish
{
public:
	Dish(std::string name, int weight, double price)
		: _name(std::move(name))
		, _weight(weight)
		, _price(price)
	{}

	virtual ~Dish() = default;

	std::string GetName()	const { return _name; }
	int			GetWeight() const { return _weight; }
	double		GetPrice()	const { return _price; }

	virtual std::string GetInfo() const
	{
		std::cout << "Dish: " << _name << ", "
			<< _weight << "g, $"
			<< std::fixed << std::setprecision(2) << _price
			<< std::endl;
	}

	virtual double GetFullPrice() const
	{
		return _price * 1.2;
	}

private:
	std::string _name;
	int			_weight;
	double		_price;
};
