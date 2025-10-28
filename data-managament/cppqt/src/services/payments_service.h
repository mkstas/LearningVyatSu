#include "../database/database.h"

#include <string>
#include <vector>
#include <iostream>

struct Payment
{
    int id;
    std::string title;
};

class PaymentsService
{
private:
    Database &_db;

public:
    PaymentsService(Database &db);

    std::vector<Payment> getAll();
};
