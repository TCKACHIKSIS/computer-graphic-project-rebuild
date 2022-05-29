#ifndef WHITENOISEINTERVAL_H
#define WHITENOISEINTERVAL_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class WhiteNoiseInterval : public BaseSimulionWindow
{
public:
    WhiteNoiseInterval(MainWindow *m_wind);
    QLineEdit *a;
    QLineEdit *b;
    void simulateSignal();
    double frand();
};

#endif // WHITENOISEINTERVAL_H
