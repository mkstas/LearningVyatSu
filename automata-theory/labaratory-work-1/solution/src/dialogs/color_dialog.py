import random
from PyQt6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel, QComboBox, 
    QMessageBox, QPushButton, QSpacerItem, QSizePolicy
)
from PyQt6.QtGui import QColor, QIcon, QPixmap, QPainter
from PyQt6.QtCore import Qt, QTimer

class ColorDialog(QDialog):
    __colors = [
        ("#000000", "Чёрный"),
        ("#800000", "Тёмно-красный"),
        ("#008000", "Зелёный"),
        ("#808000", "Оливковый"),
        ("#000080", "Тёмно-синий"),
        ("#800080", "Фиолетовый"),
        ("#008080", "Бирюзовый"),
        ("#c0c0c0", "Светло-серый"),
        ("#808080", "Серый"),
        ("#ff0000", "Красный"),
        ("#00ff00", "Светло-зеленый"),
        ("#ffff00", "Жёлтый"),
        ("#0000ff", "Синий"),
        ("#ff00ff", "Розовый"),
        ("#00ffff", "Голубой"),
        ("#ffffff", "Белый")
    ]

    def __init__(self, parent=None, people=[]):
        super().__init__(parent)

        self.people = people
        self.updated_people = []
        self.comboboxes = []
        self.current_colors = {}
        self.initial_colors = {}
        self.current_msg = None

        self._setup_dialog_properties()
        self._initialize_color_data()
        self._init_ui()

    def _setup_dialog_properties(self):
        self.setWindowTitle("Выбор цвета")
        self.setFixedSize(640, 480)

    def _initialize_color_data(self):
        for person in self.people:
            self.current_colors[person['id']] = person['color']
            self.initial_colors[person['id']] = person['color']

    def _init_ui(self):
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addSpacing(0)
        self.main_layout.setContentsMargins(8, 8, 8, 2)

        self._create_color_rows()
        self._create_button_panel()

    def _create_color_rows(self):
        for person in self.people:
            self._add_color_row(person)

    def _add_color_row(self, person):
        h_layout = QHBoxLayout()

        label = self._create_person_label(person)
        combo = self._create_color_combo(person)

        h_layout.addWidget(label)
        h_layout.addWidget(combo)

        self.main_layout.addLayout(h_layout)
        self.comboboxes.append(combo)

    def _create_person_label(self, person):
        label = QLabel(f"Рыбак {person['id'] + 1}:")
        label.setFixedWidth(100)
        return label

    def _create_color_combo(self, person):
        combo = QComboBox()
        
        combo.blockSignals(True)
        self._populate_color_combo(combo)
        self._set_initial_color(combo, person)
        combo.blockSignals(False)

        combo.currentIndexChanged.connect(
            lambda index, cb=combo, pid=person['id']: self._on_color_changed(cb, pid)
        )

        return combo

    def _populate_color_combo(self, combo):
        for color_hex, color_name in self.__colors:
            icon = self._create_color_icon(color_hex)
            combo.addItem(icon, " " + color_name, color_hex)

    def _set_initial_color(self, combo, person):
        current_index = combo.findData(person['color'])
        combo.setCurrentIndex(current_index)

    def _create_color_icon(self, color_hex):
        pixmap = QPixmap(20, 20)
        pixmap.fill(Qt.GlobalColor.transparent)
        
        painter = QPainter(pixmap)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)

        painter.setBrush(QColor("#000000"))
        painter.setPen(Qt.PenStyle.NoPen)
        painter.drawRoundedRect(0, 0, 20, 20, 2, 2)
        painter.setBrush(QColor(color_hex))
        painter.drawRoundedRect(1, 1, 18, 18, 2, 2)

        painter.end()

        return QIcon(pixmap)

    def _create_button_panel(self):
        h_layout = QHBoxLayout()

        h_layout.addSpacerItem(QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum))

        cancel_button = self._create_button("Отмена", self.reject)
        random_button = self._create_button("Случайно", self._randomize_colors)
        ok_button = self._create_button("Ок", self.accept)

        h_layout.addWidget(cancel_button)
        h_layout.addWidget(random_button)
        h_layout.addWidget(ok_button)

        h_layout.addSpacerItem(QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum))

        self.main_layout.addLayout(h_layout)

    def _create_button(self, text, callback):
        button = QPushButton(text)
        button.setFixedWidth(100)
        button.clicked.connect(callback)
        return button

    def _on_color_changed(self, combo, person_id):
        new_color = combo.currentData()

        if self._is_color_used(new_color, combo):
            self._revert_color_selection(combo, person_id)
            self._show_color_warning(new_color)
        else:
            self.current_colors[person_id] = new_color

    def _is_color_used(self, color, current_combo):
        for combo in self.comboboxes:
            if combo != current_combo and combo.currentData() == color:
                return True
        return False

    def _revert_color_selection(self, combo, person_id):
        combo.blockSignals(True)
        previous_color = self.current_colors[person_id]
        previous_index = combo.findData(previous_color)
        combo.setCurrentIndex(previous_index)
        combo.blockSignals(False)

    def _show_color_warning(self, color_hex):
        if self.current_msg:
            self.current_msg.close()

        self.current_msg = QMessageBox(self)
        self.current_msg.setIcon(QMessageBox.Icon.Warning)
        self.current_msg.setWindowTitle("Предупреждение")
        self.current_msg.setText(f"{self._get_color_name(color_hex)} цвет уже занят.")
        # self.current_msg.setStandardButtons(QMessageBox.StandardButton.NoButton)
        self.current_msg.open()

        QTimer.singleShot(1500, self.current_msg.close)

    def _get_color_name(self, color_hex):
        for hex_val, name in self.__colors:
            if hex_val == color_hex:
                return name
        return color_hex

    def _randomize_colors(self):
        available_colors = [color[0] for color in self.__colors]        
        random.shuffle(available_colors)
        selected_colors = available_colors[:len(self.comboboxes)]

        self._block_combo_signals(True)

        for i, combo in enumerate(self.comboboxes):
            color_hex = selected_colors[i]
            color_index = combo.findData(color_hex)
            if color_index >= 0:
                combo.setCurrentIndex(color_index)
                person_id = self.people[i]['id']
                self.current_colors[person_id] = color_hex

        self._block_combo_signals(False)

    def _block_combo_signals(self, block):
        for combo in self.comboboxes:
            combo.blockSignals(block)

    def _reset_to_initial(self):
        self._block_combo_signals(True)
        
        for i, person in enumerate(self.people):
            initial_color = self.initial_colors[person['id']]
            initial_index = self.comboboxes[i].findData(initial_color)
            if initial_index >= 0:
                self.comboboxes[i].setCurrentIndex(initial_index)
                self.current_colors[person['id']] = initial_color

        self._block_combo_signals(False)

    def reject(self):
        self._reset_to_initial()
        super().reject()

    def get_updated_people(self):
        updated_people = []
        for i, person in enumerate(self.people):
            updated_person = person.copy()
            updated_person['color'] = self.comboboxes[i].currentData()
            updated_people.append(updated_person)
        return updated_people

    def accept(self):
        self.updated_people = self.get_updated_people()
        super().accept()
