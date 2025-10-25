from PyQt6.QtWidgets import (
    QMainWindow, QWidget, QHBoxLayout
)
from windows.views.user_payments_view import UserPaymentsView

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        central_widget = QWidget()

        main_layout = QHBoxLayout(central_widget)
        main_layout.setContentsMargins(8, 0, 0, 0)
        main_layout.addSpacing(0)
        main_layout.addWidget(UserPaymentsView())

        self.setWindowTitle("User Payments")
        self.setFixedSize(1366, 768)
        self.setCentralWidget(central_widget)

        with open('main.qss', 'r') as f:
            styles = f.read()
            self.setStyleSheet(styles)
