from PyQt6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel, QSpinBox, QPushButton, QSpacerItem, QSizePolicy
)
from PyQt6.QtGui import QIntValidator

class InitialDialog(QDialog):
    def __init__(self, parent=None, people=[]):
        super().__init__(parent)

        self.people = [person.copy() for person in people]
        self.original_people = people
        self.spinboxes = []
        self.person_id_to_index = {}

        self._setup_dialog_properties()
        self._initialize_person_mapping()
        self._init_ui()

    def _setup_dialog_properties(self):
        self.setWindowTitle("Начальное заполнение")
        self.setFixedSize(640, 480)

    def _initialize_person_mapping(self):
        self.person_id_to_index = {person["id"]: idx for idx, person in enumerate(self.people)}

    def _init_ui(self):
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addSpacing(0)
        self.main_layout.setContentsMargins(8, 8, 8, 2)

        self._create_person_rows()
        self._create_button_panel()

    def _create_person_rows(self):
        for person in self.people:
            self._add_person_row(person)

    def _add_person_row(self, person):
        h_layout = QHBoxLayout()

        label = self._create_person_label(person)
        spinbox = self._create_spinbox(person)

        h_layout.addWidget(label)
        h_layout.addWidget(spinbox)

        self.main_layout.addLayout(h_layout)
        self.spinboxes.append(spinbox)

    def _create_person_label(self, person):
        label = QLabel(f"Рыбак {person['id'] + 1}:")
        label.setFixedWidth(100)
        return label

    def _create_spinbox(self, person):
        spinbox = QSpinBox()
        spinbox.setRange(0, 9)
        spinbox.setValue(person["count"])
        spinbox.person_id = person["id"]

        self._setup_spinbox_validation(spinbox)
        return spinbox

    def _setup_spinbox_validation(self, spinbox):
        validator = QIntValidator(0, 9, self)
        spinbox.lineEdit().setValidator(validator)

        spinbox.lineEdit().textChanged.connect(
            lambda text, sb=spinbox: self._prevent_leading_zeros(sb, text)
        )
        spinbox.editingFinished.connect(
            lambda sb=spinbox: self._final_validation(sb)
        )

    def _create_button_panel(self):
        h_layout = QHBoxLayout()

        h_layout.addSpacerItem(QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum))

        cancel_button = self._create_button("Отмена", self.reject)
        clear_button = self._create_button("Очистить", self._clear_all)
        ok_button = self._create_button("Ок", self.accept)

        h_layout.addWidget(cancel_button)
        h_layout.addWidget(clear_button)
        h_layout.addWidget(ok_button)

        h_layout.addSpacerItem(QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum))

        self.main_layout.addLayout(h_layout)

    def _create_button(self, text, callback):
        button = QPushButton(text)
        button.setFixedWidth(100)
        button.clicked.connect(callback)
        return button

    def _prevent_leading_zeros(self, spinbox, text):
        if text and len(text) > 1 and text.startswith('0'):
            clean_text = text.lstrip('0') or '0'
            spinbox.lineEdit().setText(clean_text)

    def _final_validation(self, spinbox):
        text = spinbox.lineEdit().text()
        if text and text.startswith('0') and len(text) > 1:
            clean_text = text.lstrip('0') or '0'
            try:
                value = int(clean_text)
                spinbox.setValue(min(max(value, spinbox.minimum()), spinbox.maximum()))
            except ValueError:
                spinbox.setValue(0)

    def _clear_all(self):
        for spinbox in self.spinboxes:
            spinbox.setValue(0)

    def accept(self):
        self._update_people_data()
        super().accept()

    def reject(self):
        self._restore_original_values()
        super().reject()

    def _update_people_data(self):
        for spinbox in self.spinboxes:
            person_id = spinbox.person_id
            if person_id in self.person_id_to_index:
                self.people[self.person_id_to_index[person_id]]["count"] = spinbox.value()

    def _restore_original_values(self):
        for spinbox in self.spinboxes:
            person_id = spinbox.person_id
            for original_person in self.original_people:
                if original_person["id"] == person_id:
                    spinbox.setValue(original_person["count"])
                    break

        self.people = [person.copy() for person in self.original_people]

    def get_updated_people(self):
        return self.people
