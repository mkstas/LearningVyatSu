#include "../database/database.h"

#include <string>
#include <vector>
#include <iostream>

struct User
{
    int id;
    std::string phone_number;
    std::string username;
};

class UsersService
{
private:
    Database &_db;

public:
    UsersService(Database &db);

    std::vector<User> getAll();
};
