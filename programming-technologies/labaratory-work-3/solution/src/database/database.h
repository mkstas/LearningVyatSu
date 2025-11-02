#pragma once

#include <pqxx/pqxx>
#include <string>

class Database
{
private:
    std::shared_ptr<pqxx::connection> connection;

    bool connect(std::string dsn);

public:
    Database(std::string dsn);

    pqxx::result execute(std::string query);
};
