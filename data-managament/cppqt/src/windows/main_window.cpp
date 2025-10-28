#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , db("dbname=dm_db user=root password=root host=localhost port=5432")
    , users_service(db)
    , payments_service(db)
    , user_payments_service(db)
{
    central_widget = new QWidget();

    main_layout = new QHBoxLayout(central_widget);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addSpacing(0);

    setWindowTitle("User Payments");
    setFixedSize(1366, 768);
    setCentralWidget(central_widget);

    users = users_service.getAll();
    payments = payments_service.getAll();
    user_payments = user_payments_service.getAll();

    MainWindow::setupForm();
    MainWindow::setupTable();

    MainWindow::loadUserPayments();
}

void MainWindow::setupForm()
{
    QVBoxLayout *form_layout = new QVBoxLayout();

    form_layout->setContentsMargins(8, 8, 2, 8);
    form_layout->addSpacing(0);
    form_layout->setAlignment(Qt::AlignTop);

    users_combobox = new QComboBox();
    
    for (const auto& user : users) {
        users_combobox->addItem(QString::fromStdString(user.phone_number), user.id);
    }

    payments_combobox = new QComboBox();

    for (const auto& payment : payments) {
        payments_combobox->addItem(QString::fromStdString(payment.title), payment.id);
    }

    card_number_input = new QLineEdit();
    card_number_input->setMaxLength(16);
    connect(card_number_input, &QLineEdit::textChanged, this, &MainWindow::validateIntInput);

    cvv_input = new QLineEdit();
    cvv_input->setMaxLength(3);
    connect(cvv_input, &QLineEdit::textChanged, this, &MainWindow::validateIntInput);

    submit_button = new QPushButton("Добавить");
    connect(submit_button, &QPushButton::clicked, this, &MainWindow::handleSubmit);

    update_button = new QPushButton("Обновить");
    update_button->setEnabled(false);
    connect(update_button, &QPushButton::clicked, this, &MainWindow::handleUpdate);

    delete_button = new QPushButton("Удалить");
    delete_button->setEnabled(false);
    connect(delete_button, &QPushButton::clicked, this, &MainWindow::handleDelete);

    clear_button = new QPushButton("Очистить");
    connect(clear_button, &QPushButton::clicked, this, &MainWindow::handleClear);

    form_layout->addWidget(new QLabel("Номер телефона"));
    form_layout->addWidget(users_combobox);
    form_layout->addWidget(new QLabel("Тип карты"));
    form_layout->addWidget(payments_combobox);
    form_layout->addWidget(new QLabel("Номер карты"));
    form_layout->addWidget(card_number_input);
    form_layout->addWidget(new QLabel("CVV код"));
    form_layout->addWidget(cvv_input);
    
    form_layout->addWidget(submit_button);
    form_layout->addWidget(update_button);
    form_layout->addWidget(delete_button);
    form_layout->addWidget(clear_button);

    QWidget *form_container = new QWidget();
    form_container->setFixedWidth(256);
    form_container->setLayout(form_layout);

    main_layout->addWidget(form_container);
}

void MainWindow::setupTable()
{
    search_input = new QLineEdit();
    search_input->setMaxLength(16);
    connect(search_input, &QLineEdit::textChanged, this, &MainWindow::validateIntInput);

    search_button = new QPushButton("Найти");
    connect(search_button, &QPushButton::clicked, this, &MainWindow::handleSearch);

    clear_search_button = new QPushButton("Очистить");
    connect(clear_search_button, &QPushButton::clicked, this, &MainWindow::handleClearSearch);

    QHBoxLayout *search_input_layout = new QHBoxLayout();
    search_input_layout->addWidget(search_input);
    search_input_layout->addWidget(search_button);
    search_input_layout->addWidget(clear_search_button);

    QVBoxLayout *search_layout = new QVBoxLayout();
    search_layout->setContentsMargins(0, 8, 8, 8);
    search_layout->addWidget(new QLabel("Поиск по номеру карты"));
    search_layout->addLayout(search_input_layout);

    QWidget *search_container = new QWidget();
    search_container->setLayout(search_layout);

    table = new QTableWidget();
    table->setColumnCount(5);   
    table->setHorizontalHeaderLabels({"Id", "Номер телефона", "Тип карты", "Номер карты", "CVV код"});
    table->setColumnWidth(0, 20);
    table->setColumnWidth(1, 120);
    table->setColumnWidth(2, 120);
    table->setColumnWidth(3, 200);
    table->setColumnWidth(4, 80);

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);

    table->setSelectionBehavior(QTableWidget::SelectRows);
    table->verticalHeader()->setVisible(false);

    connect(table, &QTableWidget::cellClicked, this, &MainWindow::selectUserPayment);

    QVBoxLayout *table_layout = new QVBoxLayout();
    table_layout->setContentsMargins(0, 0, 0, 0);
    table_layout->addSpacing(0);

    table_layout->addWidget(search_container);
    table_layout->addWidget(table);

    QWidget *table_container = new QWidget();
    table_container->setLayout(table_layout);

    main_layout->addWidget(table_container);
}

void MainWindow::validateIntInput(const QString &text)
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

void MainWindow::loadUserPayments()
{
    user_payments = user_payments_service.getAll();

    table->setRowCount(user_payments.size());

    for (int row = 0; row < user_payments.size(); row++) {
        const auto& user = user_payments[row];
        table->setItem(row, 0, new QTableWidgetItem(QString::number(user.id)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(user.phone_number)));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(user.title)));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(user.card_number)));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(user.cvv)));
    }
}

void MainWindow::selectUserPayment(int row, int column)
{
    QTableWidgetItem* item_id = table->item(row, 0);

    selected_user_payment_id = item_id->text().toInt();

    QTableWidgetItem *phone_number_item = table->item(row, 1);
    QTableWidgetItem *payment_item = table->item(row, 2);
    QTableWidgetItem *card_number_item = table->item(row, 3);
    QTableWidgetItem *cvv_item = table->item(row, 4);

    int phone_number_idx = users_combobox->findText(phone_number_item->text());
    users_combobox->setCurrentIndex(phone_number_idx);

    int payment_idx = payments_combobox->findText(payment_item->text());
    payments_combobox->setCurrentIndex(payment_idx);

    card_number_input->setText(card_number_item->text());
    cvv_input->setText(cvv_item->text());

    submit_button->setEnabled(false);
    update_button->setEnabled(true);
    delete_button->setEnabled(true);
}

void MainWindow::handleSubmit()
{
    int user_id = users_combobox->currentData().toInt();
    int payment_id = payments_combobox->currentData().toInt();
    QString card_number = card_number_input->text();
    QString cvv = cvv_input->text();

    if (card_number.isEmpty() || cvv.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля обязательны для заполнения");
        return;
    }

    for (const auto& payment : user_payments) {
        if (payment.card_number == card_number) {
            QMessageBox::warning(this, "Ошибка добавления", "Запись с такими данными уже существует");
            return;
        }
    }

    UserPaymentDto dto;

    dto.user_id = user_id;
    dto.payment_id = payment_id;
    dto.card_number = card_number.toStdString();
    dto.cvv = cvv.toStdString();

    user_payments_service.create(dto);

    MainWindow::handleClear();
    MainWindow::loadUserPayments();
}

void MainWindow::handleUpdate()
{
    int user_id = users_combobox->currentData().toInt();
    int payment_id = payments_combobox->currentData().toInt();
    QString card_number = card_number_input->text();
    QString cvv = cvv_input->text();

    if (card_number.isEmpty() || cvv.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля обязательны для заполнения");
        return;
    }

    UserPaymentDto dto;

    dto.user_id = user_id;
    dto.payment_id = payment_id;
    dto.card_number = card_number.toStdString();
    dto.cvv = cvv.toStdString();

    user_payments_service.update(selected_user_payment_id, dto);

    MainWindow::handleClear();
    MainWindow::loadUserPayments();
}

void MainWindow::handleDelete()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Подтверждение",
        "Удалить способ оплаты?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        user_payments_service.remove(selected_user_payment_id);
        handleClear();
        loadUserPayments();
    }
}

void MainWindow::handleClear()
{
    users_combobox->setCurrentIndex(0);
    payments_combobox->setCurrentIndex(0);
    card_number_input->clear();
    cvv_input->clear();
    selected_user_payment_id = -1;
    submit_button->setEnabled(true);
    update_button->setEnabled(false);
    delete_button->setEnabled(false);
    table->clearSelection();
}

void MainWindow::handleSearch()
{
    QString search = search_input->text();

    if (search.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле поиска обязательно для заполнения");
        return;
    }

    user_payments = user_payments_service.getBySearch(search.toStdString());

    if (user_payments.size() == 0) {
        QMessageBox::warning(this, "Ошибка", "Способы оплаты не найдены");
        return;
    }

    table->setRowCount(user_payments.size());

    for (int row = 0; row < user_payments.size(); row++) {
        const auto& user = user_payments[row];
        table->setItem(row, 0, new QTableWidgetItem(QString::number(user.id)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(user.phone_number)));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(user.title)));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(user.card_number)));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(user.cvv)));
    }
}

void MainWindow::handleClearSearch()
{
    search_input->clear();

    MainWindow::loadUserPayments();
}
