#include "main_window.h"

Product MainWindow::convertToProduct(const InternalProduct& internal) {
    return Product(
        internal.id,
        QString::fromStdString(internal.title),
        QString::fromStdString(internal.image_url),
        internal.price
    );
}

MainWindow::MainWindow(QWidget *parent, const char* dsn)
    : QMainWindow(parent)
    , product_repo(dsn ? dsn : "dbname=pt_db user=root password=root host=localhost port=5432")
{
    if (!product_repo.isConnected()) {
        QMessageBox::critical(this, "Ошибка", 
            "Не удалось подключиться к базе данных. Убедитесь, что:\n"
            "1. PostgreSQL запущен\n"
            "2. productdb.dll, libpqxx.dll, libpq.dll находятся в папке с программой\n"
            "3. База данных pt_db существует");
    }

    central_widget = new QWidget();

    main_layout = new QVBoxLayout(central_widget);
    main_layout->setContentsMargins(8, 8, 8, 8);
    main_layout->addSpacing(0);

    setWindowTitle("Cpp Qt");
    setFixedSize(768, 480);
    setCentralWidget(central_widget);

    menu_bar = this->menuBar();

    product_menu = menu_bar->addMenu("Продукты");

    show_products_action = product_menu->addAction("Отобразить продукты");
    create_product_action = product_menu->addAction("Добавление продукта");
    update_product_action = product_menu->addAction("Обновление продукта");
    delete_product_action = product_menu->addAction("Удалить продкут");

    update_product_action->setDisabled(true);
    delete_product_action->setDisabled(true);

    connect(show_products_action, &QAction::triggered, this, &MainWindow::onShowProducts);
    connect(create_product_action, &QAction::triggered, this, &MainWindow::onCreateProduct);
    connect(update_product_action, &QAction::triggered, this, &MainWindow::onUpdateProduct);
    connect(delete_product_action, &QAction::triggered, this, &MainWindow::onDeleteProduct);
}

MainWindow::~MainWindow() {
}

void MainWindow::onShowProducts()
{
    if (!product_repo.isConnected()) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к базе данных");
        return;
    }

    auto internalProducts = product_repo.getAll();
    products.clear();
    
    for (const auto& internal : internalProducts) {
        products.push_back(convertToProduct(internal));
    }

    if (!table) {
        setupTable();
    }

    updateTable();
}

void MainWindow::onCreateProduct() {
    CreateProductModal *modal = new CreateProductModal(&product_repo, this);

    if (modal->exec() == QDialog::Accepted) {
        onShowProducts();
    }
}

void MainWindow::onUpdateProduct()
{
    UpdateProductModal *modal = new UpdateProductModal(&product_repo, selected_product_id, this);

    if (modal->exec() == QDialog::Accepted) {
        onShowProducts();
    }
}

void MainWindow::onDeleteProduct()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Подтверждение удаления", 
        "Вы уверены, что хотите удалить запись?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        product_repo.remove(selected_product_id);
        update_product_action->setDisabled(true);
        delete_product_action->setDisabled(true);
        selected_product_id = -1;
        onShowProducts();
    }
}

void MainWindow::setupTable()
{
    table = new QTableWidget();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"ID", "Название", "Ссылка на изображение", "Цена"});
    table->setSelectionBehavior(QTableWidget::SelectRows);
    table->verticalHeader()->setVisible(false);

    table->setColumnWidth(0, 20);
    table->setColumnWidth(3, 100);

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);

    connect(table, &QTableWidget::cellClicked, this, &MainWindow::selectProduct);

    main_layout->addWidget(table);
}

void MainWindow::updateTable()
{
    table->setRowCount(products.size());

    for (int row = 0; row < products.size(); row++) {
        const auto& product = products[row];
        table->setItem(row, 0, new QTableWidgetItem(QString::number(product.id)));
        table->setItem(row, 1, new QTableWidgetItem(product.title));
        table->setItem(row, 2, new QTableWidgetItem(product.image_url));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(product.price)));
    }
}

void MainWindow::selectProduct(int row, int column)
{
    selected_product_id = table->item(row, 0)->text().toInt();

    update_product_action->setDisabled(false);
    delete_product_action->setDisabled(false);
}
