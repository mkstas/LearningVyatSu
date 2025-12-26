#include "update_product_modal.h"

UpdateProductModal::UpdateProductModal(ProductRepositoryWrapper *repo, int product_id, QWidget *parent)
    : QDialog(parent), product_repo(repo), product_id(product_id)
{
    // Загружаем ассемблерную библиотеку
    hValidateLib = LoadLibraryA("validate_int_lib.dll");
    if (hValidateLib)
    {
        validateIntInputAsm = reinterpret_cast<bool (*)(const char *)>(
            GetProcAddress(hValidateLib, "validateIntInputAsm"));
    }

    main_layout = new QVBoxLayout();
    setWindowTitle("Обновление продукта");
    setFixedSize(480, 300);
    setLayout(main_layout);

    if (product_repo && product_repo->isConnected())
    {
        products = product_repo->getAll();
    }

    setupForm();
    setupButtons();
    loadProductData();
}

UpdateProductModal::~UpdateProductModal()
{
    if (hValidateLib)
    {
        FreeLibrary(hValidateLib);
    }
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
    if (!product_repo || !product_repo->isConnected())
    {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к базе данных");
        reject();
        return;
    }

    auto product = product_repo->getById(product_id);
    if (product.id != -1)
    {
        title_input->setText(QString::fromStdString(product.title));
        image_url_input->setText(QString::fromStdString(product.image_url));
        price_input->setText(QString::number(product.price));
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Продукт не найден.");
        reject();
    }
}

void UpdateProductModal::handleSubmit()
{
    if (!product_repo || !product_repo->isConnected())
    {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к базе данных");
        return;
    }

    QString title = title_input->text().trimmed();
    QString image_url = image_url_input->text().trimmed();
    QString price = price_input->text().trimmed();

    if (title.isEmpty() || image_url.isEmpty() || price.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка обновления", "Все поля обязательны для заполнения.");
        return;
    }

    for (const auto &product : products)
    {
        if (product.title == title.toStdString() && product.id != product_id)
        {
            QMessageBox::warning(this, "Ошибка обновления", "Продукт с таким названием уже существует.");
            return;
        }
    }

    InternalProductDto dto;
    dto.title = title.toStdString();
    dto.image_url = image_url.toStdString();
    dto.price = price.toInt();

    bool success = product_repo->update(product_id, dto);

    if (success)
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка обновления", "Не удалось обновить продукт.");
    }
}

void UpdateProductModal::validateIntInput(const QString &text)
{
    std::string stdStr = text.toStdString();
    if (!validateIntInputAsm(stdStr.c_str()))
    {
        QLineEdit *sender = qobject_cast<QLineEdit *>(this->sender());
        if (sender && !text.isEmpty())
        {
            sender->setText(text.left(text.length() - 1));
            QMessageBox::warning(this, "Ошибка ввода", "Разрешены только цифры");
        }
    }
}

void UpdateProductModal::onCancelClick()
{
    reject();
}
