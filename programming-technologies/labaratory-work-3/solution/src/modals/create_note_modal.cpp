#include "create_note_modal.h"

CreateNoteModal::CreateNoteModal(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Добавление заметки");
    setFixedSize(480, 160);
    
    main_layout = new QVBoxLayout();
    button_layout = new QHBoxLayout();
    
    note_label = new QLabel("Заметка");
    note_input = new QLineEdit();
    
    submit_button = new QPushButton("Ок");
    cancel_button = new QPushButton("Отмена");
    
    button_layout->addWidget(cancel_button);
    button_layout->addWidget(submit_button);
    
    main_layout->addWidget(note_label);
    main_layout->addWidget(note_input);
    main_layout->addStretch();
    main_layout->addLayout(button_layout);
    
    setLayout(main_layout);
}
