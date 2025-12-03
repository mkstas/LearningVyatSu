#ifndef PRODUCT_REPOSITORY_WRAPPER_H
#define PRODUCT_REPOSITORY_WRAPPER_H

#ifdef PRODUCT_QT_LIB_EXPORTS
    #define PRODUCT_QT_LIB_API __declspec(dllexport)
#else
    #define PRODUCT_QT_LIB_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <windows.h>
#include <QString>

struct InternalProductDto {
    std::string title;
    std::string image_url;
    int price;
};

struct InternalProduct {
    int id;
    std::string title;
    std::string image_url;
    int price;
};

class PRODUCT_QT_LIB_API ProductRepositoryWrapper {
private:
    HMODULE hLib = nullptr;
    void* repo = nullptr;
    
    struct ProductDto_C {
        const char* title;
        const char* image_url;
        int price;
    };

    struct Product_C {
        int id;
        char* title;
        char* image_url;
        int price;
    };

    using CreateRepoFunc = void*(__cdecl*)(const char*);
    using DestroyRepoFunc = void(__cdecl*)(void*);
    using CreateFunc = bool(__cdecl*)(void*, const void*);
    using GetAllFunc = int(__cdecl*)(void*, void**, size_t*);
    using GetByIdFunc = bool(__cdecl*)(void*, int, void*);
    using UpdateFunc = bool(__cdecl*)(void*, int, const void*);
    using RemoveFunc = bool(__cdecl*)(void*, int);
    using FreeProductsFunc = void(__cdecl*)(void*, size_t);
    using FreeProductFunc = void(__cdecl*)(void*);

    CreateRepoFunc create_product_repository = nullptr;
    DestroyRepoFunc destroy_product_repository = nullptr;
    CreateFunc product_repo_create = nullptr;
    GetAllFunc product_repo_get_all = nullptr;
    GetByIdFunc product_repo_get_by_id = nullptr;
    UpdateFunc product_repo_update = nullptr;
    RemoveFunc product_repo_remove = nullptr;
    FreeProductsFunc product_repo_free_products = nullptr;
    FreeProductFunc product_repo_free_product = nullptr;

    bool loadLibrary();

public:
    ProductRepositoryWrapper(const std::string& dsn);
    ~ProductRepositoryWrapper();

    bool create(const InternalProductDto& dto);
    std::vector<InternalProduct> getAll();
    InternalProduct getById(int id);
    bool update(int id, const InternalProductDto& dto);
    bool remove(int id);

    bool isConnected() const { return repo != nullptr; }
};

#endif
