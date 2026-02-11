#pragma once

#include <string>

class Dish
{
public:
	Dish(std::string name, int weight, float price)
		: _name(name), _weight(weight), _price(price)
	{
	}

	std::string GetName() const
	{
		return _name;
	}

	int GetWeight() const
	{
		return _weight;
	}

	float GetPrice() const
	{
		return _price;
	}

	virtual std::string GetInfo() const = 0;
	virtual float GetFullPrice() const = 0;

private:
	std::string _name;
	int _weight;
	float _price;
};
