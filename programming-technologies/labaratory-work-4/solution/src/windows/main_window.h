#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <qaction.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>

#include "prodlib.h"

#include "../modals/create_product_modal.h"
#include "../modals/update_product_modal.h"

class MainWindow : public QMainWindow
{
private:
    prodlib::Database db;

    prodlib::ProductService product_service;

    int selected_product_id;
    
    std::vector<prodlib::Product> products;

    QWidget *central_widget;
    QVBoxLayout *main_layout;

    QMenuBar *menu_bar;
    QMenu *product_menu;

    QAction *show_products_action;
    QAction *create_product_action;
    QAction *update_product_action;
    QAction *delete_product_action;

    QTableWidget *table = nullptr;

private slots:
    void onShowProducts();
    void onCreateProduct();
    void onUpdateProduct();
    void onDeleteProduct();

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setupTable();
    void updateTable();

    void selectProduct(int row, int column);
};
