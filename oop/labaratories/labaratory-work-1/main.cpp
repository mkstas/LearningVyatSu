#include <iostream>
#include "dish.h"
#include "pizza.h"
#include "salad.h"

int main()
{
	Dish sushi("Philadelphia", 320, 15);
	Pizza pizza("Margarita", 450, 12);
	Salad salad("Caesar", 250, 9);

	std::cout << "--------------------------------" << std::endl;

	sushi.DisplayInfo();
	std::cout << "Full price: $" << sushi.GetFullPrice() << std::endl;

	std::cout << "--------------------------------" << std::endl;

	pizza.DisplayInfo();
	std::cout << "Full price: $" << pizza.GetFullPrice() << std::endl;
	pizza.ChangeDough();
	std::cout << "Full price: $" << pizza.GetFullPrice() << std::endl;
	pizza.CutInSlices();

	std::cout << "--------------------------------" << std::endl;

	salad.DisplayInfo();
	std::cout << "Full price: $" << salad.GetFullPrice() << std::endl;
	salad.TossWithDressing();
	salad.ChangeDressing();
	std::cout << "Full price: $" << salad.GetFullPrice() << std::endl;
	salad.TossWithDressing();

	std::cout << "--------------------------------" << std::endl;
}
