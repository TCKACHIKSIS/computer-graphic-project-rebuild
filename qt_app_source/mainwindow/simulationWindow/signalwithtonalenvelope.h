#ifndef SIGNALWITHTONALENVELOPE_H
#define SIGNALWITHTONALENVELOPE_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class SignalWithTonalEnvelope : public BaseSimulionWindow
{
public:
    QLineEdit *a;
    QLineEdit *m;
    QLineEdit *f0;
    QLineEdit *fn;
    QLineEdit *fi;
    SignalWithTonalEnvelope(MainWindow *m_wind);
    void simulateSignal();
};

#endif // SIGNALWITHTONALENVELOPE_H
