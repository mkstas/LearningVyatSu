#include "../include/product_qt_lib.h"
#include "windows/main_window.h"
#include <QApplication>

extern "C" PRODUCT_QT_LIB_API int run_product_app(int argc, char *argv[], const char* dsn)
{
    QApplication app(argc, argv);

    MainWindow window(nullptr, dsn);
    window.show();

    return app.exec();
}

extern "C" PRODUCT_QT_LIB_API QMainWindow* create_main_window(const char* dsn, QWidget* parent)
{
    return new MainWindow(parent, dsn);
}
