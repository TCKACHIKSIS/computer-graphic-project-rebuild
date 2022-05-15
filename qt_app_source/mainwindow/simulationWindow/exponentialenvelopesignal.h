#ifndef EXPONENTIALENVELOPESIGNAL_H
#define EXPONENTIALENVELOPESIGNAL_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class ExponentialEnvelopeSignal : public BaseSimulionWindow
{
public:
    QLineEdit *a;
    QLineEdit *tau;
    QLineEdit *f;
    QLineEdit *fi;
    ExponentialEnvelopeSignal(MainWindow *m_wind);
    void simulateSignal();
};

#endif // EXPONENTIALENVELOPESIGNAL_H
