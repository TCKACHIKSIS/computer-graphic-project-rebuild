#ifndef DELAYEDSINGLEPULSEWINDOW_H
#define DELAYEDSINGLEPULSEWINDOW_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>
#include <QLineEdit>

class DelayedSinglePulseWindow : public BaseSimulionWindow
{
public:
    DelayedSinglePulseWindow(MainWindow *mwind);
    QLineEdit *n_0;

    void simulateSignal();
};

#endif // DELAYEDSINGLEPULSEWINDOW_H
