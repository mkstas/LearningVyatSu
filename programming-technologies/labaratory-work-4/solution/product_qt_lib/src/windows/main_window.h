#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#ifdef PRODUCT_QT_LIB_EXPORTS
    #define PRODUCT_QT_LIB_API __declspec(dllexport)
#else
    #define PRODUCT_QT_LIB_API __declspec(dllimport)
#endif

#include "../product_repository_wrapper.h"
#include "../include/product_qt_lib.h"
#include "../modals/create_product_modal.h"
#include "../modals/update_product_modal.h"

#include <vector>

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>

class PRODUCT_QT_LIB_API MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ProductRepositoryWrapper product_repo;

    int selected_product_id;

    std::vector<Product> products;

    QWidget *central_widget;
    QVBoxLayout *main_layout;

    QMenuBar *menu_bar;
    QMenu *product_menu;

    QAction *show_products_action;
    QAction *create_product_action;
    QAction *update_product_action;
    QAction *delete_product_action;

    QTableWidget *table = nullptr;

    Product convertToProduct(const InternalProduct& internal);

private slots:
    void onShowProducts();
    void onCreateProduct();
    void onUpdateProduct();
    void onDeleteProduct();

public:
    explicit MainWindow(QWidget *parent = nullptr, const char* dsn = nullptr);
    ~MainWindow();

    void setupTable();
    void updateTable();

    void selectProduct(int row, int column);
};

#endif
