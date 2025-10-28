#include "../services/users_service.h"
#include "../services/payments_service.h"
#include "../services/user_payments_service.h"

#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
private:
    Database db;

    UsersService users_service;
    PaymentsService payments_service;
    UserPaymentsService user_payments_service;

    int selected_user_payment_id;

    std::vector<User> users;
    std::vector<Payment> payments;
    std::vector<UserPayment> user_payments;

    QWidget *central_widget;
    QHBoxLayout *main_layout;

    QComboBox *users_combobox;
    QComboBox *payments_combobox;
    QLineEdit *card_number_input;
    QLineEdit *cvv_input;
    QPushButton *submit_button;
    QPushButton *update_button;
    QPushButton *delete_button;
    QPushButton *clear_button;

    QLineEdit *search_input;
    QPushButton *search_button;
    QPushButton *clear_search_button;
    QTableWidget *table;

private slots:
    void validateIntInput(const QString &text);

public:
    MainWindow(QWidget *parent = nullptr);

    void setupForm();
    void setupTable();

    void loadUserPayments();
    void selectUserPayment(int row, int column);

    void handleSubmit();
    void handleUpdate();
    void handleDelete();
    void handleClear();
    void handleSearch();
    void handleClearSearch();
};
