#include "../include/appdb.h"

#include <pqxx/pqxx>
#include <iostream>
#include <format>
#include <vector>
#include <cstring>
#include <memory>

static char* cstr_dup(const std::string& s)
{
    if (s.empty()) return nullptr;
    char* p = static_cast<char*>(std::malloc(s.size() + 1));
    if (p) std::memcpy(p, s.c_str(), s.size() + 1);
    return p;
}

class ProductRepository
{
private:
    std::shared_ptr<pqxx::connection> conn;

    bool connect(const std::string& dsn)
    {
        if (dsn.empty()) return false;
        try {
            conn = std::make_shared<pqxx::connection>(dsn);
            if (conn->is_open()) {
                std::cout << "Connected to database: " << conn->dbname() << '\n';
                return true;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "DB connection failed: " << e.what() << '\n';
        }
        return false;
    }

    void exec(const std::string& sql)
    {
        pqxx::work txn(*conn);
        txn.exec(sql);
        txn.commit();
    }

public:
    explicit ProductRepository(const char* dsn)
    {
        connect(dsn ? dsn : "");
    }

    bool is_connected() const noexcept
    {
        return conn && conn->is_open();
    }

    bool create(const ProductDto& dto)
    {
        if (!dto.title || !dto.image_url) return false;
        try {
            exec(std::format(
                "INSERT INTO products (title, image_url, price) VALUES ({}, {}, {})",
                conn->quote(dto.title),
                conn->quote(dto.image_url),
                dto.price
            ));
            return true;
        }
        catch (...) { return false; }
    }

    std::vector<Product> getAll()
    {
        std::vector<Product> result;
        try {
            pqxx::result r = pqxx::work(*conn).exec("SELECT id, title, image_url, price FROM products ORDER BY id");
            for (const auto& row : r) {
                Product p{};
                p.id        = row["id"].as<int>();
                p.title     = cstr_dup(row["title"].as<std::string>());
                p.image_url = cstr_dup(row["image_url"].as<std::string>());
                p.price     = row["price"].as<int>();
                result.push_back(p);
            }
        }
        catch (...) {}
        return result;
    }

    bool getById(int id, Product& out)
    {
        try {
            pqxx::result r = pqxx::work(*conn).exec(std::format("SELECT id, title, image_url, price FROM products WHERE id = {}", id));
            if (r.empty()) return false;
            const auto& row = r[0];
            out.id        = row["id"].as<int>();
            out.title     = cstr_dup(row["title"].as<std::string>());
            out.image_url = cstr_dup(row["image_url"].as<std::string>());
            out.price     = row["price"].as<int>();
            return true;
        }
        catch (...) { return false; }
    }

    bool update(int id, const ProductDto& dto)
    {
        if (!dto.title || !dto.image_url) return false;
        try {
            exec(std::format(
                "UPDATE products SET title = {}, image_url = {}, price = {} WHERE id = {}",
                conn->quote(dto.title),
                conn->quote(dto.image_url),
                dto.price, id
            ));
            return true;
        }
        catch (...) { return false; }
    }

    bool remove(int id)
    {
        try {
            exec(std::format("DELETE FROM products WHERE id = {}", id));
            return true;
        }
        catch (...) { return false; }
    }
};

extern "C" {

void* create_product_repository(const char* dsn)
{
    auto* repo = new ProductRepository(dsn);
    if (repo->is_connected())
        return repo;
    delete repo;
    return nullptr;
}

void destroy_product_repository(void* repo)
{
    delete static_cast<ProductRepository*>(repo);
}

bool product_repo_create(void* repo, const ProductDto* dto)
{
    return repo && dto && static_cast<ProductRepository*>(repo)->create(*dto);
}

int product_repo_get_all(void* repo, Product** out_products, size_t* out_count)
{
    if (!repo || !out_products || !out_count) return -1;
    auto vec = static_cast<ProductRepository*>(repo)->getAll();
    if (vec.empty()) {
        *out_products = nullptr;
        *out_count = 0;
        return 0;
    }
    *out_products = static_cast<Product*>(std::malloc(vec.size() * sizeof(Product)));
    if (!*out_products) return -1;
    std::memcpy(*out_products, vec.data(), vec.size() * sizeof(Product));
    *out_count = vec.size();
    return 0;
}

bool product_repo_get_by_id(void* repo, int id, Product* out)
{
    return repo && out && static_cast<ProductRepository*>(repo)->getById(id, *out);
}

bool product_repo_update(void* repo, int id, const ProductDto* dto)
{
    return repo && dto && static_cast<ProductRepository*>(repo)->update(id, *dto);
}

bool product_repo_remove(void* repo, int id)
{
    return repo && static_cast<ProductRepository*>(repo)->remove(id);
}

void product_repo_free_products(Product* products, size_t count)
{
    if (!products) return;
    for (size_t i = 0; i < count; ++i) {
        std::free(products[i].title);
        std::free(products[i].image_url);
    }
    std::free(products);
}

void product_repo_free_product(Product* p)
{
    if (!p) return;
    std::free(p->title);
    std::free(p->image_url);
}

}
