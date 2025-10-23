from PyQt6.QtWidgets import (
    QWidget, QHBoxLayout, QVBoxLayout, QLineEdit, QLabel,
    QTableWidget, QTableWidgetItem, QPushButton, QMessageBox,
    QHeaderView, QComboBox
)
from controllers.user_controller import UserController
from controllers.payments_controller import PaymentsController
from controllers.user_payments_controller import UserPaymentsController

class UserPaymentsView(QWidget):
    selected_user_payment_id = None

    def __init__(self):
        super().__init__()

        self.user_controller = UserController()
        self.payments_controller = PaymentsController()
        self.user_payments_controller = UserPaymentsController()
        self.main_layout = QHBoxLayout(self)
        self.main_layout.setContentsMargins(0, 0, 0, 0)

        self.user_payments = []

        self.setup_form()
        self.setup_table()
        self.load_user_payments()

    def setup_form(self):
        form_container = QWidget()
        form_container.setFixedWidth(256)

        form_layout = QVBoxLayout()
        form_layout.setContentsMargins(0, 0, 0, 0)

        users = self.user_controller.get_users()
        self.users_combobox = QComboBox()
        for user in users:
            self.users_combobox.addItem(user[1], userData=user[0])

        payments = self.payments_controller.get_payments()
        self.payments_combobox = QComboBox()
        for payment in payments:
            self.payments_combobox.addItem(payment[1], userData=payment[0])

        self.card_number_input = QLineEdit()
        self.card_number_input.setMaxLength(16)
        self.card_number_input.textChanged.connect(self.validate_input)

        self.cvv_input = QLineEdit()
        self.cvv_input.setMaxLength(3)
        self.cvv_input.textChanged.connect(self.validate_input)

        self.submit_btn = QPushButton("Добавить")
        self.submit_btn.clicked.connect(self.handle_submit)

        self.update_btn = QPushButton("Обновить")
        self.update_btn.clicked.connect(self.handle_update)
        self.update_btn.setEnabled(False)

        self.delete_btn = QPushButton("Удалить")
        self.delete_btn.clicked.connect(self.handle_delete)
        self.delete_btn.setEnabled(False)

        self.clear_btn = QPushButton("Очистить")
        self.clear_btn.clicked.connect(self.handle_clear)

        form_layout.addWidget(QLabel("Номер телефона"))
        form_layout.addWidget(self.users_combobox)
        form_layout.addWidget(QLabel("Тип карты"))
        form_layout.addWidget(self.payments_combobox)
        form_layout.addWidget(QLabel("Номер карты"))
        form_layout.addWidget(self.card_number_input)
        form_layout.addWidget(QLabel("CVV код"))
        form_layout.addWidget(self.cvv_input)
        form_layout.addWidget(self.submit_btn)
        form_layout.addWidget(self.update_btn)
        form_layout.addWidget(self.delete_btn)
        form_layout.addWidget(self.clear_btn)

        form_layout.addStretch()
        form_layout.setContentsMargins(0, 8, 0, 0)
        form_container.setLayout(form_layout)

        self.main_layout.addWidget(form_container)

    def setup_table(self):
        main_container = QWidget()

        search_container = QWidget()

        table_layout = QVBoxLayout()
        table_layout.setContentsMargins(0, 0, 0, 0)
        table_layout.setSpacing(0)

        search_layout = QVBoxLayout()
        search_layout.setContentsMargins(8, 8, 8, 8)

        search_input_layout = QHBoxLayout()
        search_input_layout.setContentsMargins(0, 0, 0, 0)

        self.search_input = QLineEdit()
        self.search_input.setMaxLength(16)
        self.search_input.textChanged.connect(self.validate_input)

        self.search_button = QPushButton("Найти")
        self.search_button.clicked.connect(self.handle_search)

        self.load_button = QPushButton("Очистить")
        self.load_button.clicked.connect(self.handle_clear_search)

        search_container.setLayout(search_layout)

        search_input_layout.addWidget(self.search_input)
        search_input_layout.addWidget(self.search_button)
        search_input_layout.addWidget(self.load_button)

        search_layout.addWidget(QLabel("Поиск по номеру карты"))
        search_layout.addLayout(search_input_layout)

        table_layout.addWidget(search_container)

        self.table = QTableWidget()
        self.table.setColumnCount(5)
        self.table.verticalHeader().setVisible(False)
        self.table.setHorizontalHeaderLabels(["Id", "Номер телефона", "Тип карты", "Номер крты", "CVV код"])
        self.table.setColumnWidth(0, 20)
        self.table.setColumnWidth(1, 120)
        self.table.setColumnWidth(2, 120)
        self.table.setColumnWidth(3, 200)
        self.table.setColumnWidth(4, 80)
        self.table.cellClicked.connect(self.select_user_payment)
        self.table.setShowGrid(False)

        self.table.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeMode.Fixed)
        self.table.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeMode.Fixed)
        self.table.horizontalHeader().setSectionResizeMode(2, QHeaderView.ResizeMode.Fixed)
        self.table.horizontalHeader().setSectionResizeMode(3, QHeaderView.ResizeMode.Fixed)
        self.table.horizontalHeader().setSectionResizeMode(4, QHeaderView.ResizeMode.Fixed)
        self.table.setSelectionBehavior(QTableWidget.SelectionBehavior.SelectRows)

        table_layout.addWidget(self.table)
        main_container.setLayout(table_layout)
        self.main_layout.addWidget(main_container)

    def validate_input(self, text):
        if text and not text.isdigit():
            self.search_input.setText(text[:-1])
            QMessageBox.warning(self, "Ошибка ввода", "Разрешены только цифры")

    def load_user_payments(self):
        self.user_payments = self.user_payments_controller.get_user_payments()

        self.table.setRowCount(len(self.user_payments))

        for row, user in enumerate(self.user_payments):
            self.table.setItem(row, 0, QTableWidgetItem(str(user[0])))
            self.table.setItem(row, 1, QTableWidgetItem(str(user[1])))
            self.table.setItem(row, 2, QTableWidgetItem(str(user[2])))
            self.table.setItem(row, 3, QTableWidgetItem(str(user[3])))
            self.table.setItem(row, 4, QTableWidgetItem(str(user[4])))

    def handle_clear_search(self):
        self.search_input.clear()
        self.load_user_payments()

    def handle_submit(self):
        user_id = self.users_combobox.currentData()
        payment_id = self.payments_combobox.currentData()
        card_number = self.card_number_input.text().strip().replace(" ", "")
        cvv = self.cvv_input.text().strip()

        if not card_number or not cvv:
            QMessageBox.warning(self, "Ошибка", "Все поля обязательны для заполнения")
            return

        for card in self.user_payments:
            if card['card_number'] == card_number:
                QMessageBox.warning(self, "Ошибка добавления", "Запись с такими данными уже существует")
                return

        self.user_payments_controller.create_user_payment(user_id, payment_id, card_number, cvv)
        self.handle_clear()
        self.load_user_payments()

    def handle_search(self):
        search = self.search_input.text().strip()

        if not search:
            QMessageBox.warning(self, "Ошибка", "Поле поиска обязательно для заполнения")
            return

        user_payments = self.user_payments_controller.get_user_payments_by_search(search)

        if (len(user_payments) == 0):
            QMessageBox.warning(self, "Записи не найдены", f"Номера карт, включающие в себя '{search}' не найдены")
            return

        self.table.setRowCount(len(user_payments))

        for row, user in enumerate(user_payments):
            self.table.setItem(row, 0, QTableWidgetItem(str(user[0])))
            self.table.setItem(row, 1, QTableWidgetItem(str(user[1])))
            self.table.setItem(row, 2, QTableWidgetItem(str(user[2])))
            self.table.setItem(row, 3, QTableWidgetItem(str(user[3])))
            self.table.setItem(row, 4, QTableWidgetItem(str(user[4])))

    def handle_update(self):
        if self.selected_user_payment_id is None:
            return

        user_id = self.users_combobox.currentData()
        payment_id = self.payments_combobox.currentData()
        card_number = self.card_number_input.text().strip().replace(" ", "")
        cvv = self.cvv_input.text().strip()

        if not card_number or not cvv:
            QMessageBox.warning(self, "Ошибка", "Все поля обязательны для заполнения")
            return

        self.user_payments_controller.update_user_payment(self.selected_user_payment_id, user_id, payment_id, card_number, cvv)
        self.handle_clear()
        self.load_user_payments()

    def handle_delete(self):
        if self.selected_user_payment_id is None:
            return

        reply = QMessageBox.question(
            self,
            "Подтверждение",
            "Удалить способ оплаты?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )

        if reply == QMessageBox.StandardButton.Yes:
            self.user_payments_controller.delete_user_payment(self.selected_user_payment_id)
            self.handle_clear()
            self.load_user_payments()

    def handle_clear(self):
        self.users_combobox.setCurrentIndex(0)
        self.payments_combobox.setCurrentIndex(0)
        self.card_number_input.clear()
        self.cvv_input.clear()
        self.selected_user_payment_id = None
        self.submit_btn.setEnabled(True)
        self.update_btn.setEnabled(False)
        self.delete_btn.setEnabled(False)
        self.table.clearSelection()

    def select_user_payment(self, row):
        item_id = self.table.item(row, 0)
        if item_id:
            self.selected_user_payment_id = int(item_id.text())

            phone_number_item = self.table.item(row, 1)
            payment_item = self.table.item(row, 2)
            card_number_item = self.table.item(row, 3)
            cvv_item = self.table.item(row, 4)

            phone_number_index = self.users_combobox.findText(phone_number_item.text())
            payment_index = self.payments_combobox.findText(payment_item.text())

            if phone_number_item:
                self.users_combobox.setCurrentIndex(phone_number_index)
            if phone_number_item:
                self.payments_combobox.setCurrentIndex(payment_index)
            if card_number_item:
                self.card_number_input.setText(card_number_item.text())
            if cvv_item:
                self.cvv_input.setText(cvv_item.text())

            self.update_btn.setEnabled(True)
            self.delete_btn.setEnabled(True)
            self.submit_btn.setEnabled(False)
