from PyQt6.QtWidgets import (
    QVBoxLayout, QDialog, QLabel, QDialogButtonBox
)
from PyQt6.QtCore import Qt

class AuthorDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Об авторе")
        self.setFixedSize(640, 360)

        layout = QVBoxLayout()
        layout.setContentsMargins(16, 8, 16, 8)
        layout.setSpacing(8)

        title_label = QLabel("Об авторе")
        title_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        title_label.setStyleSheet("""
            font-size: 18px;
            font-weight: bold;
            margin: 8px 0;
        """)

        name_label = QLabel("Выполнил: Макаров Станислав Алексеевич")
        name_label.setAlignment(Qt.AlignmentFlag.AlignLeft)
        name_label.setStyleSheet("""
            font-size: 14px;
        """)

        group_label = QLabel("Группа: ИВТб-2301-05-00")
        group_label.setAlignment(Qt.AlignmentFlag.AlignLeft)
        group_label.setStyleSheet("""
            font-size: 14px;
            margin-top: 4px;
        """)

        button_box = QDialogButtonBox(QDialogButtonBox.StandardButton.Ok)
        button_box.accepted.connect(self.accept)
        button_box.setStyleSheet("""
            font-size: 12px;
            width: 100px;
        """)

        layout.addWidget(title_label)
        layout.addWidget(name_label)
        layout.addWidget(group_label)
        layout.addStretch()
        layout.addWidget(button_box, 0, Qt.AlignmentFlag.AlignCenter)

        self.setLayout(layout)
