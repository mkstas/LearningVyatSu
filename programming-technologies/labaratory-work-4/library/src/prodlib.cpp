#include "../include/prodlib.h"

namespace prodlib {
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

    ProductService::ProductService(Database &db) : _db(db) {}

    bool ProductService::create(ProductDto dto)
    {
        try
        {
            _db.execute(
                std::format(
                    "INSERT INTO products (title, image_url, price) "
                    "VALUES ('{}', '{}', {})",
                    dto.title,
                    dto.image_url,
                    std::to_string(dto.price)
                )
            );

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Create product error: " << e.what() << std::endl;
            return false;
        }
    }

    std::vector<Product> ProductService::getAll()
    {
        std::vector<Product> products;

        try
        {
            pqxx::result result = _db.execute(
                "SELECT * FROM products"
            );

            for (const auto& row : result) {
                Product product;

                product.id = row[0].as<int>();
                product.title = row[1].as<std::string>();
                product.image_url = row[2].as<std::string>();
                product.price = row[3].as<int>();

                products.push_back(product);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Get all products error: " << e.what() << std::endl;
        }
        
        return products;
    }

    Product ProductService::getById(int id)
    {
        try
        {
            pqxx::result result = _db.execute(
                std::format("SELECT * FROM products WHERE id = {}", id)
            );

            if (!result.empty()) {
                const auto& row = result[0];
                Product product;
                product.id = row[0].as<int>();
                product.title = row[1].as<std::string>();
                product.image_url = row[2].as<std::string>();
                product.price = row[3].as<int>();
                return product;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Get product by id error: " << e.what() << std::endl;
        }
        
        return Product{-1, "", "", 0};
    }

    bool ProductService::update(int id, ProductDto dto)
    {
        try
        {
            _db.execute(
                std::format(
                    "UPDATE products SET "
                        "title = '{}', "
                        "image_url = '{}', "
                        "price = {} "
                    "WHERE id = {}",
                    dto.title,
                    dto.image_url,
                    dto.price,
                    id
                )
            );

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Update product error: " << e.what() << std::endl;
            return false;
        }
    }

    bool ProductService::remove(int id)
    {
        try
        {
            _db.execute(
                std::format("DELETE FROM products WHERE id = {}", id)
            );

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Remove product error: " << e.what() << std::endl;
            return false;
        }
    }
}
