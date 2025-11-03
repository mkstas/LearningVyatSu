#include "main_window.h"
#include "../modals/create_note_modal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();

    main_layout = new QVBoxLayout(central_widget);
    main_layout->setContentsMargins(12, 12, 12, 12);
    main_layout->addSpacing(0);

    setWindowTitle("CppQt");
    setFixedSize(640, 480);
    setCentralWidget(central_widget);

    setupCreateNoteButton();
}

void MainWindow::setupCreateNoteButton()
{
    create_note_open = new QPushButton("Добавить заметку");
    connect(create_note_open, &QPushButton::clicked, this, &MainWindow::onCreateNoteClicked);

    main_layout->addWidget(create_note_open);
    main_layout->addStretch();
}

void MainWindow::onCreateNoteClicked()
{
    CreateNoteModal modal(this);
    modal.exec();
}
