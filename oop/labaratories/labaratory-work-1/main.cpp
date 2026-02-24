#include <iostream>
#include <vector>
#include "dish.h"
#include "pizza.h"
#include "salad.h"

int main()
{
	std::vector<std::unique_ptr<Dish>> dishes;

	dishes.push_back(std::make_unique<Pizza>());
	dishes.push_back(std::make_unique<Pizza>("Pepperoni"));
	dishes.push_back(std::make_unique<Pizza>("Margarita", 450, 12));
	dishes.push_back(std::make_unique<Salad>("Caesar", 250, 9));

	dynamic_cast<Pizza*>(dishes[0].get())->CutInSlices();
}
