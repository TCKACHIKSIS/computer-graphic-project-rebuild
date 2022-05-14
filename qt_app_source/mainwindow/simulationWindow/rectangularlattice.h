#ifndef RECTANGULARLATTICE_H
#define RECTANGULARLATTICE_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class RectangularLattice : public BaseSimulionWindow
{
public:
    RectangularLattice( MainWindow *m_wind);
    QLineEdit *L;
    void simulateSignal();
};

#endif // RECTANGULARLATTICE_H
