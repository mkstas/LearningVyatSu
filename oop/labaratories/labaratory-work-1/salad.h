#pragma once

#include <iostream>
#include "dish.h"

enum Dressing
{
	OliveOil,
	Mayonnaise
};

class Salad : public Dish
{
public:
	Salad(std::string name, int weight, double price)
		: Dish(name, weight, price)
	{}

	std::string GetDressing() const
	{
		return _dressing == Dressing::OliveOil ? "olive oil" : "mayonnaise";
	}

	void ChangeDressing()
	{
		_dressing = _dressing == Dressing::OliveOil ? Dressing::Mayonnaise : Dressing::OliveOil;
	}

	void TossWithDressing() const
	{
		std::cout << "Tossing the salad with " << GetDressing() << "..." << std::endl;
	}

	void DisplayInfo() const override
	{
		std::cout << "Salad: " << GetName() << ", "
			<< GetDressing() << " dressing, "
			<< std::to_string(GetWeight()) << "g, $"
			<< std::fixed << std::setprecision(2) << GetFullPrice()
			<< std::endl;
	}

	double GetFullPrice() const override
	{
		return _dressing == OliveOil ? GetPrice() * 1.4 : GetPrice() * 1.3;
	}

private:
	Dressing _dressing = Dressing::OliveOil;
};
