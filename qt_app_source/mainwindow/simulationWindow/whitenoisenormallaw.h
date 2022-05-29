#ifndef WHITENOISENORMALLAW_H
#define WHITENOISENORMALLAW_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class WhiteNoiseNormalLaw : public BaseSimulionWindow
{
public:
    WhiteNoiseNormalLaw(MainWindow *m_wind);
    void simulateSignal();
    double frand();
    double getn();
    QLineEdit *a;
    QLineEdit *q2;
};

#endif // WHITENOISENORMALLAW_H
