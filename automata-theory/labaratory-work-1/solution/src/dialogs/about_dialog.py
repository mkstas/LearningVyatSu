from PyQt6.QtWidgets import (
    QVBoxLayout, QDialog, QLabel, QDialogButtonBox
)
from PyQt6.QtCore import Qt

class AboutDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("О программе")
        self.setFixedSize(640, 360)

        layout = QVBoxLayout()
        layout.setContentsMargins(16, 8, 16, 8)
        layout.setSpacing(8)

        title_label = QLabel("О программе")
        title_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        title_label.setStyleSheet("""
            font-size: 18px;
            font-weight: bold;
            margin: 8px 0;
        """)

        description_label = QLabel(
            "Рыбаки\n\n"
            "- Есть 10 рыбаков\n"
            "- У каждого в начале от 0 до 9 рыб\n"
            "- Случайным образом выбирается рыбак и ему добавляется 1 рыба\n"
            "- При срабатывании аварийной лампы случайно выбирается рыбак, у которого от 1 до 9 рыб\n"
            "- Игра заканчивается, когда все поймали по 10 рыб"
        )
        description_label.setAlignment(Qt.AlignmentFlag.AlignLeft)
        description_label.setStyleSheet("""
            font-size: 14px;
            margin: 8px 0;
            line-height: 1.4;
        """)
        description_label.setWordWrap(True)

        button_box = QDialogButtonBox(QDialogButtonBox.StandardButton.Ok)
        button_box.accepted.connect(self.accept)
        button_box.setStyleSheet("""
            font-size: 12px;
            width: 100px;
        """)

        layout.addWidget(title_label)
        layout.addWidget(description_label)
        layout.addStretch()
        layout.addWidget(button_box, 0, Qt.AlignmentFlag.AlignCenter)

        self.setLayout(layout)
