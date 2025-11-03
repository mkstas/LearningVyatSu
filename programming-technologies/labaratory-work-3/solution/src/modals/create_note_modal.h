#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class CreateNoteModal : public QDialog
{
private:
    QVBoxLayout *main_layout;
    QHBoxLayout *button_layout;

    QLabel *note_label;
    QLineEdit *note_input;
    QPushButton *submit_button;
    QPushButton *cancel_button;

public:
    explicit CreateNoteModal(QWidget *parent = nullptr);
};
