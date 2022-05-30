#ifndef AUTOREGRESSIVEMOVINGAVERAGEORDERSIGNAL_H
#define AUTOREGRESSIVEMOVINGAVERAGEORDERSIGNAL_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class AutoregressiveMovingAverageOrderSignal : public BaseSimulionWindow
{
public:
    AutoregressiveMovingAverageOrderSignal(MainWindow *m_wind);
    void simulateSignal();
    double frand();
    double getn();
    QLineEdit *p;
    QLineEdit *q;
    QLineEdit *q2;
};

#endif // AUTOREGRESSIVEMOVINGAVERAGEORDERSIGNAL_H
