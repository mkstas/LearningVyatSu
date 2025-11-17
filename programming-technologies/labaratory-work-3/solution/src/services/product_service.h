#pragma once

#include "../database/database.h"

#include <vector>
#include <string>
#include <format>
#include <iostream>

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
