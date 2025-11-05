#include "database.h"

#include <iostream>

Database::Database(std::string dsn)
{
    Database::connect(dsn);
}

bool Database::connect(std::string dsn)
{
    try
    {
        connection = std::make_shared<pqxx::connection>(dsn);

        if (connection->is_open()) {
            std::cout << "Connected to database: " << connection->dbname() << std::endl;

            return true;
        } else {
            std::cout << "Failed to connect to database: " << dsn << std::endl;

            return false;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Database connection error: " << e.what() << std::endl;

        return false;
    }
}

pqxx::result Database::execute(const std::string query)
{
    try
    {
        pqxx::work txn(*connection);

        auto result = txn.exec(query);

        txn.commit();

        return result;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Query execution error: " << e.what() << std::endl;
    }
}
