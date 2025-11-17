#pragma once

#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include <vector>
#include <format>

namespace prodlib {
    class Database
    {
    private:
        std::shared_ptr<pqxx::connection> connection;

        bool connect(std::string dsn);

    public:
        Database(std::string dsn);

        pqxx::result execute(std::string query);
    };

    struct Product
    {
        int id;
        std::string title;
        std::string image_url;
        int price;
    };

    struct ProductDto {
        std::string title;
        std::string image_url;
        int price;
    };

    class ProductService
    {
    private:
        Database &_db;

    public:
        ProductService(Database &db);

        bool create(ProductDto dto);
        std::vector<Product> getAll();
        Product getById(int id);
        bool update(int id, ProductDto dto);
        bool remove(int id);
    };
}
