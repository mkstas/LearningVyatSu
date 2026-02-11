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
	Salad(std::string name, int weight, float price)
		: Dish(name, weight, price)
	{
	}

	std::string GetDressing() const
	{
		return _dressing == Dressing::OliveOil ? "olive oil" : "mayonnaise";
	}

	std::string GetInfo() const override
	{
		return "Pizza: " + GetName() + ", " + GetDressing() + " dough, " + std::to_string(GetWeight()) + "g, $" + std::to_string(GetFullPrice());
	}

	float GetFullPrice() const override
	{
		return _dressing == OliveOil ? GetPrice() * 1.1f : GetPrice() * 1.3f;
	}

	void ChangeDressing()
	{
		_dressing = _dressing == Dressing::OliveOil ? Dressing::Mayonnaise : Dressing::OliveOil;
	}

	void TossWithDressing() const
	{
		std::cout << "Tossing the salad with " << GetDressing() << "..." << std::endl;
	}

private:
	Dressing _dressing = Dressing::OliveOil;
};
#pragma once
