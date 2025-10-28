#include "../database/database.h"

#include <string>
#include <format>
#include <vector>
#include <iostream>

struct UserPayment
{
    int id;
    std::string phone_number;
    std::string title;
    std::string card_number;
    std::string cvv;
};

struct UserPaymentDto
{
    int user_id;
    int payment_id;
    std::string card_number;
    std::string cvv;
};

class UserPaymentsService
{
private:
    Database &_db;

public:
    UserPaymentsService(Database &db);

    std::vector<UserPayment> getAll();
    std::vector<UserPayment> getBySearch(const std::string substring);
    bool create(UserPaymentDto dto);
    bool update(int id, UserPaymentDto dto);
    bool remove(int id);
};
