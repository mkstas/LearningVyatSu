#pragma once

#include <iostream>
#include "dish.h"

enum Dough
{
	Thin,
	Thick
};

class Pizza : public Dish
{
public:
	Pizza(std::string name, int weight, float price)
		: Dish(name, weight, price)
	{
	}

	std::string GetDough() const
	{
		return _dough == Dough::Thin ? "thin" : "thick";
	}

	std::string GetInfo() const override
	{
		return "Pizza: " + GetName() + ", " + GetDough() + " dough, " + std::to_string(GetWeight()) + "g, $" + std::to_string(GetFullPrice());
	}

	float GetFullPrice() const override
	{
		return _dough == Thin ? GetPrice() * 1.2f : GetPrice() * 1.4f;
	}

	void ChangeDough()
	{
		_dough = _dough == Dough::Thin ? Dough::Thick : Dough::Thin;
	}

	void CutInSlices()
	{
		std::cout << "Cutting the pizza into slices..." << std::endl;
	}

private:
	Dough _dough = Dough::Thick;
};
