import json
import random
from PyQt6.QtCore import Qt, QTimer, QPropertyAnimation, QEasingCurve
from PyQt6.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QDialog, QFileDialog,
    QLineEdit, QSlider, QPushButton, QMessageBox, QLabel
)
from PyQt6.QtGui import QAction
from dialogs.author_dialog import AuthorDialog
from dialogs.about_dialog import AboutDialog
from dialogs.color_dialog import ColorDialog
from dialogs.initial_dialog import InitialDialog
from widgets.person import Person

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.speed = 30
        self.alarm = 15
        self.people = [
            {"id": 0, "count": 2, "color": "#000000"},
            {"id": 1, "count": 4, "color": "#800000"},
            {"id": 2, "count": 1, "color": "#008000"},
            {"id": 3, "count": 1, "color": "#808000"},
            {"id": 4, "count": 0, "color": "#000080"},
            {"id": 5, "count": 5, "color": "#800080"},
            {"id": 6, "count": 3, "color": "#008080"},
            {"id": 7, "count": 1, "color": "#c0c0c0"},
            {"id": 8, "count": 4, "color": "#808080"},
            {"id": 9, "count": 2, "color": "#ff0000"}
        ]

        self.game_timer = None
        self.is_running = False
        self.is_paused = False
        self.initial_people = []
        self.character_widgets = []
        self.current_msg = None

        self._setup_ui()
        self._initialize_game()

    def _setup_ui(self):
        self.setWindowTitle("Рыбаки")
        self.setFixedSize(1366, 768)

        central_widget = QWidget()
        self.main_layout = QVBoxLayout(central_widget)
        self.main_layout.setContentsMargins(0, 0, 0, 0)
        self.main_layout.setSpacing(0)
        self.setCentralWidget(central_widget)

        self._init_menu_bar()
        self._init_area()
        self._init_controls()

    def _initialize_game(self):
        self._initialize_people_data()
        self.update_controls()
        self.update_characters_display()

        self.game_timer = QTimer()
        self.game_timer.timeout.connect(self.game_tick)

    def _initialize_people_data(self):
        self.initial_people = []
        for i, person in enumerate(self.people):
            self.initial_people.append({
                'color': person['color'],
                'count': person['count']
            })
            self.people[i]['id'] = i

    def _init_menu_bar(self):
        menu_bar = self.menuBar()
        self._init_file_menu(menu_bar)
        self._init_settings_menu(menu_bar)
        self._init_reference_menu(menu_bar)

    def _init_file_menu(self, menu_bar):
        file_menu = menu_bar.addMenu("Файл")

        self.open_file_action = QAction("Открыть", self)
        self.save_file_action = QAction("Сохранить", self)
        exit_action = QAction("Выход", self)

        self.open_file_action.triggered.connect(self.open_file)
        self.save_file_action.triggered.connect(self.save_file)
        exit_action.triggered.connect(self.close)

        file_menu.addActions([self.open_file_action, self.save_file_action])
        file_menu.addSeparator()
        file_menu.addAction(exit_action)

    def _init_settings_menu(self, menu_bar):
        settings_menu = menu_bar.addMenu("Настройки")

        self.colors_action = QAction("Выбор цвета", self)
        self.initial_action = QAction("Начальное заполнение", self)

        self.colors_action.triggered.connect(self.show_color_dialog)
        self.initial_action.triggered.connect(self.show_initial_dialog)

        settings_menu.addActions([self.colors_action, self.initial_action])

    def _init_reference_menu(self, menu_bar):
        reference_menu = menu_bar.addMenu("Справка")

        author_action = QAction("Об авторе", self)
        about_menu = QAction("О программе", self)

        author_action.triggered.connect(lambda: AuthorDialog(self).exec())
        about_menu.triggered.connect(lambda: AboutDialog(self).exec())

        reference_menu.addActions([author_action, about_menu])

    def _init_controls(self):
        controls_container = QWidget()
        controls_layout = QHBoxLayout()
        controls_layout.setContentsMargins(8, 8, 8, 8)

        self._create_control_buttons(controls_layout)
        self._create_speed_controls(controls_layout)
        self._create_alarm_controls(controls_layout)

        controls_container.setLayout(controls_layout)
        self.main_layout.addWidget(controls_container)

    def _create_control_buttons(self, layout):
        self.start_button = QPushButton("Старт")
        self.pause_button = QPushButton("Пауза")
        self.exit_button = QPushButton("Выход")

        self.start_button.setStyleSheet("""width: 80px;""")
        self.pause_button.setStyleSheet("""width: 80px;""")
        self.exit_button.setStyleSheet("""width: 80px;""")

        self.start_button.clicked.connect(self.toggle_game)
        self.pause_button.clicked.connect(self.toggle_pause)
        self.exit_button.clicked.connect(self.close)

        self.pause_button.setEnabled(True)

        layout.addWidget(self.start_button)
        layout.addWidget(self.pause_button)
        layout.addWidget(self.exit_button)

    def _create_speed_controls(self, layout):
        speed_label = QLabel("Скорость")
        speed_label.setFixedWidth(60)

        self.speed_slider = QSlider(Qt.Orientation.Horizontal)
        self.speed_slider.setRange(0, 100)

        self.speed_input = QLineEdit()
        self.speed_input.setFixedWidth(40)

        self.speed_slider.valueChanged.connect(self.on_speed_changed)
        self.speed_input.textChanged.connect(self.on_speed_input_changed)

        layout.addWidget(speed_label)
        layout.addWidget(self.speed_slider)
        layout.addWidget(self.speed_input)

    def _create_alarm_controls(self, layout):
        alarm_label = QLabel("Аварийная лампа")
        alarm_label.setFixedWidth(110)

        self.alarm_slider = QSlider(Qt.Orientation.Horizontal)
        self.alarm_slider.setRange(0, 100)

        self.alarm_input = QLineEdit()
        self.alarm_input.setFixedWidth(40)

        self.alarm_lamp = QLabel()
        self.alarm_lamp.setFixedSize(20, 20)
        self._set_alarm_lamp_style("#ffffff")
        self.alarm_lamp.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.alarm_slider.valueChanged.connect(self.on_alarm_changed)
        self.alarm_input.textChanged.connect(self.on_alarm_input_changed)

        layout.addWidget(alarm_label)
        layout.addWidget(self.alarm_slider)
        layout.addWidget(self.alarm_input)
        layout.addWidget(self.alarm_lamp)

    def _init_area(self):
        self.area_container = QWidget()
        self.area_container.setStyleSheet("""
            QWidget {
                background-color: #f1f5f9;
                border-top: 1px solid #e2e8f0;
            }
        """)

        self.area_layout = QHBoxLayout()
        self.area_layout.setContentsMargins(16, 16, 16, 16)
        self.area_layout.setSpacing(16)
        self.area_layout.setAlignment(Qt.AlignmentFlag.AlignVCenter)

        self._create_character_widgets()
        self.area_container.setLayout(self.area_layout)
        self.main_layout.addWidget(self.area_container, 1)

    def _create_character_widgets(self):
        for i in range(10):
            character_widget = self._create_character_widget()
            self.character_widgets.append(character_widget)
            self.area_layout.addWidget(character_widget['widget'])

    def _create_character_widget(self):
        character_widget = QWidget()
        character_widget.setStyleSheet("border: none")

        character_layout = QVBoxLayout()
        character_layout.setAlignment(Qt.AlignmentFlag.AlignCenter)
        character_layout.setSpacing(10)

        count_label = QLabel("0")
        count_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self._set_count_label_style(count_label, "black")

        Person_widget = Person()
        Person_widget.setFixedSize(112, 220)

        character_layout.addWidget(count_label)
        character_layout.addWidget(Person_widget)
        character_widget.setLayout(character_layout)

        return {
            'widget': character_widget,
            'Person_widget': Person_widget,
            'count_label': count_label,
            'highlight_timer': None,
            'animation': None
        }

    def _set_count_label_style(self, label, color):
        label.setStyleSheet(f"""
            font-size: 32px; 
            font-weight: bold;
            padding: 5px;
            color: {color};
        """)

    def _set_alarm_lamp_style(self, color, border_color=None):
        border_style = f"border: 1px solid {border_color};" if border_color else ""
        self.alarm_lamp.setStyleSheet(f"""
            QLabel {{
                background-color: {color};
                border-radius: 10px;
                {border_style}
            }}
        """)

    def _validate_numeric_input(self, text, current_value, input_field, setter_method, field_name):
        if text == "":
            setter_method(0)
            self._update_input_field(input_field, 0)
            return False

        if not text.isdigit():
            self._update_input_field(input_field, current_value)
            self._show_input_error("Ошибка ввода", "Разрешено вводить только числовые значения.")
            return False

        value = int(text)

        if text.count('0') == len(text) and len(text) > 1:
            self._update_input_field(input_field, current_value)
            return False

        if current_value == 0:
            if value == 0:
                return True
            else:
                if value <= 100:
                    setter_method(value)
                    return True
                else:
                    self._update_input_field(input_field, current_value)
                    self._show_input_error("Недопустимое значение", f"{field_name} должна быть в диапазоне от 0 до 100.")
                    return False

        if text.startswith('0') and len(text) > 1:
            self._update_input_field(input_field, current_value)
            self._show_input_error("Недопустимое значение", "Число не должно начинаться с нуля.")
            return False

        if value > 100:
            self._update_input_field(input_field, current_value)
            self._show_input_error("Недопустимое значение", f"{field_name} должна быть в диапазоне от 0 до 100.")
            return False

        setter_method(value)
        return True

    def _show_input_error(self, title, message):
        if self.current_msg:
            self.current_msg.close()

        self.current_msg = QMessageBox(self)
        self.current_msg.setIcon(QMessageBox.Icon.Warning)
        self.current_msg.setWindowTitle(title)
        self.current_msg.setText(message)
        # self.current_msg.setStandardButtons(QMessageBox.StandardButton.NoButton)
        self.current_msg.open()

        QTimer.singleShot(1500, self.current_msg.close)
        # QMessageBox.warning(self, title, message)

    def _show_input_info(self, title, message):
        QMessageBox.information(self, title, message)

    def _update_input_field(self, input_field, value):
        input_field.blockSignals(True)
        input_field.setText(str(value))
        input_field.blockSignals(False)

    def on_speed_changed(self, value):
        self._update_input_field(self.speed_input, value)
        self.speed = value
        self._update_game_timer_interval()

    def on_alarm_changed(self, value):
        self._update_input_field(self.alarm_input, value)
        self.alarm = value

    def on_speed_input_changed(self, text):
        self._validate_numeric_input(text, self.speed, self.speed_input, self._set_speed_value, "Скорость")

    def on_alarm_input_changed(self, text):
        self._validate_numeric_input(text, self.alarm, self.alarm_input, self._set_alarm_value, "Аварийная лампа")

    def _set_speed_value(self, value):
        self.speed = value
        self.speed_slider.setValue(value)
        self._update_game_timer_interval()

    def _set_alarm_value(self, value):
        self.alarm = value
        self.alarm_slider.setValue(value)

    def _update_game_timer_interval(self):
        if self.is_running and not self.is_paused:
            interval = max(10, 1000 - self.speed * 7)
            self.game_timer.setInterval(interval)

    def update_controls(self):
        self.speed_slider.setValue(self.speed)
        self.speed_input.setText(str(self.speed))

        self.alarm_slider.setValue(self.alarm)
        self.alarm_input.setText(str(self.alarm))

    def update_characters_display(self):
        if not hasattr(self, 'character_widgets') or not self.character_widgets:
            return
            
        for i, character_data in enumerate(self.character_widgets):
            if i < len(self.people):
                self._update_character_display(i, character_data)
            else:
                self._reset_character_display(character_data)

    def _update_character_display(self, index, character_data):
        person = self.people[index]
        character_data['Person_widget'].update_color(person['color'])
        character_data['count_label'].setText(str(person['count']))

        color = "#16a34a" if person['count'] >= 10 else "black"
        self._set_count_label_style(character_data['count_label'], color)

    def _reset_character_display(self, character_data):
        character_data['Person_widget'].update_color("#ffffff")
        character_data['count_label'].setText("0")
        self._set_count_label_style(character_data['count_label'], "black")

    def update_character_display(self, index):
        if index < len(self.people) and index < len(self.character_widgets):
            character_data = self.character_widgets[index]
            self._update_character_display(index, character_data)

    def highlight_character(self, index):
        if self._is_valid_character_index(index):
            self._animate_Person_movement(index)
            self._start_highlight_timer(index, self.restore_character_style, 200)

    def highlight_character_with_red_counter(self, index):
        if self._is_valid_character_index(index):
            character_data = self.character_widgets[index]
            self._set_count_label_style(character_data['count_label'], "#ef4444")
            self._animate_Person_movement(index)
            self._start_highlight_timer(index, self.restore_character_style_after_alarm, 500)

    def _is_valid_character_index(self, index):
        return index < len(self.character_widgets) and index < len(self.people)

    def _animate_Person_movement(self, index):
        character_data = self.character_widgets[index]
        Person_widget = character_data['Person_widget']

        animation = QPropertyAnimation(Person_widget, b"geometry")
        animation.setDuration(300)
        animation.setEasingCurve(QEasingCurve.Type.OutInQuad)

        current_geometry = Person_widget.geometry()
        down_geometry = current_geometry.translated(0, 20)

        animation.setKeyValueAt(0, current_geometry)
        animation.setKeyValueAt(0.5, down_geometry)
        animation.setKeyValueAt(1, current_geometry)

        animation.start()
        character_data['animation'] = animation

    def _start_highlight_timer(self, index, callback, timeout):
        character_data = self.character_widgets[index]
        
        if character_data['highlight_timer']:
            character_data['highlight_timer'].stop()

        character_data['highlight_timer'] = QTimer()
        character_data['highlight_timer'].setSingleShot(True)
        character_data['highlight_timer'].timeout.connect(lambda: callback(index))
        character_data['highlight_timer'].start(timeout)

    def restore_character_style(self, index):
        if self._is_valid_character_index(index):
            character_data = self.character_widgets[index]
            character_data['Person_widget'].setStyleSheet("")

    def restore_character_style_after_alarm(self, index):
        if self._is_valid_character_index(index):
            character_data = self.character_widgets[index]
            person = self.people[index]
            
            color = "#16a34a" if person['count'] >= 10 else "black"
            self._set_count_label_style(character_data['count_label'], color)
            character_data['Person_widget'].setStyleSheet("")

    def trigger_alarm_lamp(self):
        self._set_alarm_lamp_style("#ef4444", "#dc2626")
        QTimer.singleShot(500, self.reset_alarm_lamp)

    def reset_alarm_lamp(self):
        self._set_alarm_lamp_style("#ffffff")

    def game_tick(self):
        if self.alarm > 0 and random.randint(1, 100) <= self.alarm:
            self.trigger_alarm()
        else:
            self.normal_game_tick()

    def normal_game_tick(self):
        available_people = [p for p in self.people if p['count'] < 10]

        if not available_people:
            self.stop_game_with_message()
            return

        selected_person = random.choice(available_people)
        person_index = self.people.index(selected_person)
        selected_person['count'] += 1

        self.update_character_display(person_index)
        self.highlight_character(person_index)

    def trigger_alarm(self):
        self.trigger_alarm_lamp()
        
        eligible_people = [p for p in self.people if 1 <= p['count'] <= 9]

        if not eligible_people:
            return

        selected_person = random.choice(eligible_people)
        person_index = self.people.index(selected_person)
        selected_person['count'] -= 1
        
        self.update_character_display(person_index)
        self.highlight_character_with_red_counter(person_index)

    def toggle_game(self):
        if not self.is_running:
            self.start_game()
        else:
            self.stop_game()

    def start_game(self):
        self.is_running = True

        self.start_button.setText("Стоп")
        self.pause_button.setText("Продолжить" if self.is_paused else "Пауза")

        self._set_menu_enabled(False)

        interval = max(10, 1000 - self.speed * 7)
        self.game_timer.setInterval(interval)

        self.update_characters_display()

        if not self.is_paused:
            self.game_timer.start()

    def stop_game(self):
        self.is_running = False
        self.is_paused = False
        self.start_button.setText("Старт")
        self.pause_button.setText("Пауза")

        self.reset_game()
        self._set_menu_enabled(True)
        self.game_timer.stop()

    def stop_game_with_message(self):
        self.is_running = False
        self.is_paused = False
        self.start_button.setText("Старт")
        self.pause_button.setText("Пауза")

        self.reset_game()
        self._set_menu_enabled(True)
        self.game_timer.stop()

        QMessageBox.information(
            self,
            "Игра завершена",
            "Нажмите 'Старт' для начала новой игры."
        )

    def _set_menu_enabled(self, enabled):
        actions = [self.open_file_action, self.save_file_action, 
                  self.colors_action, self.initial_action]
        for action in actions:
            action.setEnabled(enabled)

    def reset_game(self):
        self.people = []
        for i, person in enumerate(self.initial_people):
            self.people.append({
                'id': i,
                'color': person['color'],
                'count': person['count']
            })

    def toggle_pause(self):
        if not self.is_running:
            self.is_paused = not self.is_paused
            self.pause_button.setText("Продолжить" if self.is_paused else "Пауза")
        else:
            if not self.is_paused:
                self.pause_game()
            else:
                self.resume_game()

    def pause_game(self):
        self.is_paused = True
        self.pause_button.setText("Продолжить")
        self.game_timer.stop()

    def resume_game(self):
        self.is_paused = False
        self.pause_button.setText("Пауза")
        self._update_game_timer_interval()
        self.game_timer.start()

    def open_file(self):
        file_path = QFileDialog.getOpenFileName(
            self,
            "Открыть файл",
            "",
            "JSON Files (*.json);;All Files (*)"
        )

        if file_path[0]:
            self.load_config(file_path[0])
            self.update_controls()
            self.update_characters_display()

    def save_file(self):
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Сохранить файл",
            "",
            "JSON Files (*.json);;All Files (*)"
        )

        if file_path:
            if not file_path.endswith('.json'):
                file_path += '.json'

            saved_data = {
                'speed': self.speed,
                'alarm': self.alarm,
                'people': self.people,
            }

            with open(file_path, 'w', encoding='utf-8') as f:
                json.dump(saved_data, f, ensure_ascii=False, indent=4)

    def load_config(self, file_path):
        """Метод для загрузки конфигурации из файла (используется при открытии файла)"""
        with open(file_path, 'r', encoding='utf-8') as f:
            data = json.load(f)

        self.speed = data['speed']
        self.alarm = data['alarm']
        self.people = data['people']
        self._initialize_people_data()

    def show_color_dialog(self):
        dialog = ColorDialog(self, people=self.people)

        if dialog.exec() == QDialog.DialogCode.Accepted:
            self.people = dialog.updated_people
            self._initialize_people_data()
            self.update_characters_display()

    def show_initial_dialog(self):
        dialog = InitialDialog(self, people=self.people)

        if dialog.exec() == QDialog.DialogCode.Accepted:
            self.people = dialog.get_updated_people()
            self._initialize_people_data()
            self.update_characters_display()
