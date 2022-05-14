#ifndef SAMPLEDSINEWAVE_H
#define SAMPLEDSINEWAVE_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>

class MainWindow;

class SampledSineWave : public BaseSimulionWindow
{
public:
    SampledSineWave(MainWindow *m_wind);
    QLineEdit *a;
    QLineEdit *w;
    QLineEdit *fi;
    void simulateSignal();
};

#endif // SAMPLEDSINEWAVE_H
