#pragma once

#include <cstddef>

struct ProductDto {
    const char* title;
    const char* image_url;
    int         price;
};

struct Product {
    int    id;
    char*  title;
    char*  image_url;
    int    price;
};

#ifdef __cplusplus
extern "C" {
#endif

void* create_product_repository(const char* dsn);
void destroy_product_repository(void* repo);
bool product_repo_create(void* repo, const ProductDto* dto);
int  product_repo_get_all(void* repo, Product** out_products, size_t* out_count);
bool product_repo_get_by_id(void* repo, int id, Product* out_product);
bool product_repo_update(void* repo, int id, const ProductDto* dto);
bool product_repo_remove(void* repo, int id);
void product_repo_free_products(Product* products, size_t count);
void product_repo_free_product(Product* product);

#ifdef __cplusplus
}
#endif
