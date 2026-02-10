#include <string>

#include "dish.h"

enum Dressing
{
    None,
    OliveOil
};

class Salad : Dish
{
private:
    Dressing _dressing = None;
    bool _is_tossed = false;

public:
    Salad(std::string name, float weight);

    void ChooseDressing(Dressing Dressing);
    void TossWithDressing();
};
