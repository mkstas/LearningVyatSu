#include "update_product_modal.h"

UpdateProductModal::UpdateProductModal(int product_id, QWidget *parent)
    : QDialog(parent)
    , db("dbname=pt_db user=root password=root host=localhost port=5432")
    , product_service(db)
    , product_id(product_id)
{
    main_layout = new QVBoxLayout();

    setWindowTitle("Обновление продукта");
    setFixedSize(480, 300);
    setLayout(main_layout);

    products = product_service.getAll();

    UpdateProductModal::setupForm();
    UpdateProductModal::setupButtons();
    UpdateProductModal::loadProductData();
}

void UpdateProductModal::setupForm()
{
    title_input = new QLineEdit();
    image_url_input = new QLineEdit();
    price_input = new QLineEdit();

    connect(price_input, &QLineEdit::textChanged, this, &UpdateProductModal::validateIntInput);

    main_layout->addWidget(new QLabel("Название продукта"));
    main_layout->addWidget(title_input);
    main_layout->addWidget(new QLabel("Ссылка на изображение"));
    main_layout->addWidget(image_url_input);
    main_layout->addWidget(new QLabel("Цена продукта"));
    main_layout->addWidget(price_input);
}

void UpdateProductModal::setupButtons()
{
    button_layout = new QHBoxLayout();

    submit_button = new QPushButton("Обновить");
    cancel_button = new QPushButton("Отмена");

    connect(submit_button, &QPushButton::clicked, this, &UpdateProductModal::handleSubmit);
    connect(cancel_button, &QPushButton::clicked, this, &UpdateProductModal::onCancelClick);

    button_layout->addWidget(submit_button);
    button_layout->addWidget(cancel_button);

    main_layout->addStretch();
    main_layout->addLayout(button_layout);
}

void UpdateProductModal::loadProductData()
{
    auto product = product_service.getById(product_id);
    if (product.id != -1) {
        title_input->setText(QString::fromStdString(product.title));
        image_url_input->setText(QString::fromStdString(product.image_url));
        price_input->setText(QString::number(product.price));
    } else {
        QMessageBox::warning(this, "Ошибка", "Продукт не найден.");
        reject();
    }
}

void UpdateProductModal::handleSubmit()
{
    QString title = title_input->text().trimmed();
    QString image_url = image_url_input->text().trimmed();
    QString price = price_input->text().trimmed();

    if (title.isEmpty() || image_url.isEmpty() || price.isEmpty()) {
        QMessageBox::warning(this, "Ошибка обновления", "Все поля обязательны для заполнения.");
        return;
    }

    for (const auto& product : products) {
        if (product.title == title.toStdString() && product.id != product_id) {
            QMessageBox::warning(this, "Ошибка обновления", "Продукт с таким названием уже существует.");
            return;
        }
    }

    ProductDto dto;
    dto.title = title.toStdString();
    dto.image_url = image_url.toStdString();
    dto.price = price.toInt();

    bool success = product_service.update(product_id, dto);

    if (success) {
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка обновления", "Не удалось обновить продукт.");
    }
}

void UpdateProductModal::validateIntInput(const QString &text)
{
    if (!text.isEmpty()) {
        for (const QChar &ch : text) {
            if (!ch.isDigit()) {
                QLineEdit *sender = qobject_cast<QLineEdit*>(this->sender());
                if (sender) {
                    QString currentText = sender->text();
                    sender->setText(currentText.left(currentText.length() - 1));
                    QMessageBox::warning(this, "Ошибка ввода", "Разрешены только цифры");
                }
                break;
            }
        }
    }
}

void UpdateProductModal::onCancelClick()
{
    reject();
}
