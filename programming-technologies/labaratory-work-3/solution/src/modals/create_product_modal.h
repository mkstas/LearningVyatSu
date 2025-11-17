#include <vector>

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

#include "../database/database.h"
#include "../services/product_service.h"

class CreateProductModal : public QDialog
{
private:
    Database db;

    ProductService product_service;

    std::vector<Product> products;

    QVBoxLayout *main_layout;
    QHBoxLayout *button_layout;

    QLineEdit *title_input;
    QLineEdit *image_url_input;
    QLineEdit *price_input;

    QPushButton *submit_button;
    QPushButton *cancel_button;

    void setupForm();
    void setupButtons();
    void handleSubmit();
    void validateIntInput(const QString &text);

private slots:
    void onCancelClick();

public:
    explicit CreateProductModal(QWidget *parent = nullptr);
};
