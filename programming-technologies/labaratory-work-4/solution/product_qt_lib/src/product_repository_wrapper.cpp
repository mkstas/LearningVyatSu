#include "product_repository_wrapper.h"
#include <iostream>
#include <cstring>

bool ProductRepositoryWrapper::loadLibrary() {
    hLib = LoadLibraryA("libproduct_db_lib.dll");

    if (!hLib) {
        std::cerr << "Library loading error: " << GetLastError() << std::endl;

        return false;
    }

    create_product_repository = (CreateRepoFunc)GetProcAddress(hLib, "create_product_repository");
    destroy_product_repository = (DestroyRepoFunc)GetProcAddress(hLib, "destroy_product_repository");
    product_repo_create = (CreateFunc)GetProcAddress(hLib, "product_repo_create");
    product_repo_get_all = (GetAllFunc)GetProcAddress(hLib, "product_repo_get_all");
    product_repo_get_by_id = (GetByIdFunc)GetProcAddress(hLib, "product_repo_get_by_id");
    product_repo_update = (UpdateFunc)GetProcAddress(hLib, "product_repo_update");
    product_repo_remove = (RemoveFunc)GetProcAddress(hLib, "product_repo_remove");
    product_repo_free_products = (FreeProductsFunc)GetProcAddress(hLib, "product_repo_free_products");
    product_repo_free_product = (FreeProductFunc)GetProcAddress(hLib, "product_repo_free_product");

    if (!create_product_repository || !destroy_product_repository || 
        !product_repo_create || !product_repo_get_all || !product_repo_get_by_id ||
        !product_repo_update || !product_repo_remove || !product_repo_free_products) {

        std::cerr << "Failed to load functions from library" << std::endl;
        FreeLibrary(hLib);
        hLib = nullptr;

        return false;
    }

    return true;
}

ProductRepositoryWrapper::ProductRepositoryWrapper(const std::string& dsn) {
    if (!loadLibrary()) {
        return;
    }

    repo = create_product_repository(dsn.c_str());

    if (!repo) {
        std::cerr << "Failed to connect to the database" << std::endl;
        FreeLibrary(hLib);
        hLib = nullptr;
    }
}

ProductRepositoryWrapper::~ProductRepositoryWrapper() {
    if (repo) {
        destroy_product_repository(repo);
    }

    if (hLib) {
        FreeLibrary(hLib);
    }
}

bool ProductRepositoryWrapper::create(const InternalProductDto& dto) {
    if (!repo) return false;

    ProductDto_C dto_c;
    dto_c.title = dto.title.c_str();
    dto_c.image_url = dto.image_url.c_str();
    dto_c.price = dto.price;

    return product_repo_create(repo, &dto_c);
}

std::vector<InternalProduct> ProductRepositoryWrapper::getAll() {
    std::vector<InternalProduct> result;

    if (!repo) return result;

    Product_C* products_c = nullptr;
    size_t count = 0;

    if (product_repo_get_all(repo, (void**)&products_c, &count) == 0 && products_c) {
        for (size_t i = 0; i < count; ++i) {
            InternalProduct product;
            product.id = products_c[i].id;
            product.title = products_c[i].title ? products_c[i].title : "";
            product.image_url = products_c[i].image_url ? products_c[i].image_url : "";
            product.price = products_c[i].price;
            result.push_back(product);
        }

        product_repo_free_products(products_c, count);
    }

    return result;
}

InternalProduct ProductRepositoryWrapper::getById(int id) {
    InternalProduct product;
    product.id = -1;

    if (!repo) return product;

    Product_C product_c;
    if (product_repo_get_by_id(repo, id, &product_c)) {
        product.id = product_c.id;
        product.title = product_c.title ? product_c.title : "";
        product.image_url = product_c.image_url ? product_c.image_url : "";
        product.price = product_c.price;

        product_repo_free_product(&product_c);
    }

    return product;
}

bool ProductRepositoryWrapper::update(int id, const InternalProductDto& dto) {
    if (!repo) return false;

    ProductDto_C dto_c;
    dto_c.title = dto.title.c_str();
    dto_c.image_url = dto.image_url.c_str();
    dto_c.price = dto.price;

    return product_repo_update(repo, id, &dto_c);
}

bool ProductRepositoryWrapper::remove(int id) {
    if (!repo) return false;

    return product_repo_remove(repo, id);
}
