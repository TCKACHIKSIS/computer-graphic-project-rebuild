#ifndef LCHMSIGNAL_H
#define LCHMSIGNAL_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class LCHMSignal : public BaseSimulionWindow
{
public:
    QLineEdit *a;
    QLineEdit *f0;
    QLineEdit *fk;
    QLineEdit *fi;

    LCHMSignal( MainWindow *m_wind );
    void simulateSignal();
};

#endif // LCHMSIGNAL_H
