#ifndef SAW_H
#define SAW_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class Saw : public BaseSimulionWindow
{
public:
    QLineEdit *L;
    Saw(MainWindow *m_wind);
    void simulateSignal();
};

#endif // SAW_H
