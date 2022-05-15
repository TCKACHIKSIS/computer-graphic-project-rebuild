#ifndef BALANCEDENVELOPESIGNAL_H
#define BALANCEDENVELOPESIGNAL_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class BalancedEnvelopeSignal : public BaseSimulionWindow
{
public:
    BalancedEnvelopeSignal(MainWindow *m_wind);
    void simulateSignal();
    QLineEdit *a;
    QLineEdit *f0;
    QLineEdit *fn;
    QLineEdit *fi;
};

#endif // BALANCEDENVELOPESIGNAL_H
