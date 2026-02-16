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
	Pizza(std::string name, int weight, double price)
		: Dish(name, weight, price)
	{}
	
	std::string GetDough() const
	{
		return _dough == Dough::Thin ? "thin" : "thick";
	}

	void ChangeDough()
	{
		_dough = _dough == Dough::Thin ? Dough::Thick : Dough::Thin;
	}

	void CutInSlices()
	{
		std::cout << "Cutting the pizza into slices..." << std::endl;
	}

	std::string GetInfo() const override
	{
		std::cout << "Pizza: " << GetName() << ", "
			<< GetDough() << " dough, "
			<< GetWeight() << "g, $"
			<< std::fixed << std::setprecision(2) << std::to_string(GetFullPrice())
			<< std::endl;
	}

	double GetFullPrice() const override
	{
		return _dough == Dough::Thin ? GetPrice() * 1.3 : GetPrice() * 1.5;
	}

private:
	Dough _dough = Dough::Thick;
};
