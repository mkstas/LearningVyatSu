#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

struct Note
{
    QString content;
};

class MainWindow : public QMainWindow
{
private:
    std::vector<Note> notes;

    QWidget *central_widget;
    QVBoxLayout *main_layout;
    QPushButton *create_note_open;

    void setupCreateNoteButton();

private slots:
    void onCreateNoteClicked();

public:
    MainWindow(QWidget *parent = nullptr);
};
