#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
private:
    QWidget *central_widget;
    QHBoxLayout *main_layout;

public:
    MainWindow(QWidget *parent = nullptr);
};
