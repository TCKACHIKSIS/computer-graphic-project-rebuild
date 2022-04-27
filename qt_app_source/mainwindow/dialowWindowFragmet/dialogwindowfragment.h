#ifndef DIALOGWINDOWFRAGMENT_H
#define DIALOGWINDOWFRAGMENT_H
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <utility>

class MainWindow;

class DialogWindowFragment : public QDialog
{
public:
    DialogWindowFragment(MainWindow *window);
    QBoxLayout *grid_layout;
    QLineEdit *start_value;
    QLineEdit *end_value;
    MainWindow *main_window;
    QPushButton *button;
public slots:
        void fragmentWasChosen();
};


#endif // DIALOGWINDOWFRAGMENT_H
