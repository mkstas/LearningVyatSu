#include "users_service.h"

UsersService::UsersService(Database &db) : _db(db) {}

std::vector<User> UsersService::getAll()
{
    std::vector<User> users;

    try
    {
        pqxx::result result = _db.execute("SELECT * FROM users");

        for (const auto& row : result) {
            User user;

            user.id = row[0].as<int>();
            user.phone_number = row[1].as<std::string>();
            user.username = row[2].as<std::string>();

            users.push_back(user);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Get all users error: " << e.what() << std::endl;
    }

    return users;
}
