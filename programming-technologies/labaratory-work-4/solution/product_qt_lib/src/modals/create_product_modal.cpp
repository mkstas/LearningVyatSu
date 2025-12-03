#include "create_product_modal.h"

CreateProductModal::CreateProductModal(ProductRepositoryWrapper* repo, QWidget *parent)
    : QDialog(parent)
    , product_repo(repo)
{
    main_layout = new QVBoxLayout();

    setWindowTitle("Добавление продукта");
    setFixedSize(480, 300);
    setLayout(main_layout);

    if (product_repo && product_repo->isConnected()) {
        products = product_repo->getAll();
    }

    setupForm();
    setupButtons();
}

void CreateProductModal::setupForm()
{
    title_input = new QLineEdit();
    image_url_input = new QLineEdit();
    price_input = new QLineEdit();

    connect(price_input, &QLineEdit::textChanged, this, &CreateProductModal::validateIntInput);

    main_layout->addWidget(new QLabel("Название продукта"));
    main_layout->addWidget(title_input);
    main_layout->addWidget(new QLabel("Ссылка на изображение"));
    main_layout->addWidget(image_url_input);
    main_layout->addWidget(new QLabel("Цена продукта"));
    main_layout->addWidget(price_input);
}

void CreateProductModal::setupButtons()
{
    button_layout = new QHBoxLayout();

    submit_button = new QPushButton("Ок");
    cancel_button = new QPushButton("Отмена");

    connect(submit_button, &QPushButton::clicked, this, &CreateProductModal::handleSubmit);
    connect(cancel_button, &QPushButton::clicked, this, &CreateProductModal::onCancelClick);

    button_layout->addWidget(submit_button);
    button_layout->addWidget(cancel_button);

    main_layout->addStretch();
    main_layout->addLayout(button_layout);
}

void CreateProductModal::handleSubmit()
{
    if (!product_repo || !product_repo->isConnected()) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к базе данных");
        return;
    }

    QString title = title_input->text().trimmed();
    QString image_url = image_url_input->text().trimmed();
    QString price = price_input->text().trimmed();

    if (title.isEmpty() || image_url.isEmpty() || price.isEmpty()) {
        QMessageBox::warning(this, "Ошибка добавления", "Все поля обязательны для заполнения.");
        return;
    }

    for (const auto& product : products) {
        if (product.title == title.toStdString()) {
            QMessageBox::warning(this, "Ошибка добавления", "Продукт с таким названием уже существует.");
            return;
        }
    }

    InternalProductDto dto;
    dto.title = title.toStdString();
    dto.image_url = image_url.toStdString();
    dto.price = price.toInt();

    if (product_repo->create(dto)) {
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка добавления", "Не удалось добавить продукт");
    }
}

void CreateProductModal::validateIntInput(const QString &text)
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

void CreateProductModal::onCancelClick()
{
    reject();
}
