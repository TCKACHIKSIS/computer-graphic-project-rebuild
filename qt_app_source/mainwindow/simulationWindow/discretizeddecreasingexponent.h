#ifndef DISCRETIZEDDECREASINGEXPONENT_H
#define DISCRETIZEDDECREASINGEXPONENT_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class DiscretizedDecreasingExponent : public BaseSimulionWindow
{
public:
    DiscretizedDecreasingExponent(MainWindow *mwind);
    void simulateSignal();
    QLineEdit *a;
};

#endif // DISCRETIZEDDECREASINGEXPONENT_H
