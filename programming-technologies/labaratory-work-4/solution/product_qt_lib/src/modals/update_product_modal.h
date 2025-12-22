#ifndef UPDATE_PRODUCT_MODAL_H
#define UPDATE_PRODUCT_MODAL_H

#ifdef PRODUCT_QT_LIB_EXPORTS
#define PRODUCT_QT_LIB_API __declspec(dllexport)
#else
#define PRODUCT_QT_LIB_API __declspec(dllimport)
#endif

#include "../product_repository_wrapper.h"
#include "../include/product_qt_lib.h"

#include <vector>
#include <windows.h>

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

class PRODUCT_QT_LIB_API UpdateProductModal : public QDialog
{
    Q_OBJECT

private:
    ProductRepositoryWrapper *product_repo;
    std::vector<InternalProduct> products;

    QVBoxLayout *main_layout;
    QHBoxLayout *button_layout;

    QLineEdit *title_input;
    QLineEdit *image_url_input;
    QLineEdit *price_input;

    QPushButton *submit_button;
    QPushButton *cancel_button;

    int product_id;

    HMODULE hValidateLib = nullptr;
    bool (*validateIntInputAsm)(const char *) = nullptr;

    void setupForm();
    void setupButtons();
    void handleSubmit();
    void validateIntInput(const QString &text);
    void loadProductData();

private slots:
    void onCancelClick();

public:
    explicit UpdateProductModal(ProductRepositoryWrapper *repo, int product_id, QWidget *parent = nullptr);
    ~UpdateProductModal();
};

#endif
