#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();

    main_layout = new QHBoxLayout(central_widget);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addSpacing(0);

    setWindowTitle("CppQt");
    setFixedSize(1366, 768);
    setCentralWidget(central_widget);
}
