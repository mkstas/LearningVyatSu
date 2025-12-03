#ifndef PRODUCT_QT_LIB_H
#define PRODUCT_QT_LIB_H

#ifdef PRODUCT_QT_LIB_EXPORTS
    #define PRODUCT_QT_LIB_API __declspec(dllexport)
#else
    #define PRODUCT_QT_LIB_API __declspec(dllimport)
#endif

#include <QApplication>
#include <QMainWindow>
#include <QString>

struct PRODUCT_QT_LIB_API ProductDto {
    QString title;
    QString image_url;
    int price;
    
    ProductDto() : price(0) {}
    ProductDto(const QString& t, const QString& i, int p) : title(t), image_url(i), price(p) {}
};

struct PRODUCT_QT_LIB_API Product {
    int id;
    QString title;
    QString image_url;
    int price;
    
    Product() : id(-1), price(0) {}
    Product(int i, const QString& t, const QString& img, int p) : id(i), title(t), image_url(img), price(p) {}
};

class ProductRepositoryWrapper;

extern "C" {
    PRODUCT_QT_LIB_API int run_product_app(int argc, char *argv[], const char* dsn);
    
    PRODUCT_QT_LIB_API QMainWindow* create_main_window(const char* dsn, QWidget* parent = nullptr);
}

#endif
