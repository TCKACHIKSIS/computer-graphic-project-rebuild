#ifndef DELAYEDSINGLEJUMP_H
#define DELAYEDSINGLEJUMP_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class DelayedSingleJump : public BaseSimulionWindow
{
public:
    DelayedSingleJump(MainWindow *mwind);
    QLineEdit *n_0;
    void simulateSignal();
};

#endif // DELAYEDSINGLEJUMP_H
