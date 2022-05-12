#ifndef BASESIMULIONWINDOW_H
#define BASESIMULIONWINDOW_H
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <filehandler/dataStructure.h>
class MainWindow;

class BaseSimulionWindow : public QDialog
{
public:
    BaseSimulionWindow(MainWindow *mwind);

    MainWindow *main_window;
    QBoxLayout *box_layout;
    QPushButton *simulation_button;

    QLineEdit *number_of_samples;
    QLineEdit *sampling_frequency;
    CanalOfSignal *new_signal = nullptr;
    bool isRecreateChannel = false;
    void readBaseParametrs();
    void createMainSignal();
};

#endif // BASESIMULIONWINDOW_H
