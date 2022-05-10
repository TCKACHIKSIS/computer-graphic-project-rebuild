#ifndef BASESIMULIONWINDOW_H
#define BASESIMULIONWINDOW_H
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
class MainWindow;

class BaseSimulionWindow : public QDialog
{
public:
    BaseSimulionWindow(MainWindow *mwind);

    MainWindow *main_window;
    QBoxLayout *box_layout;
    QPushButton *simulation_button;

    virtual void simulateSignal();
};

#endif // BASESIMULIONWINDOW_H
