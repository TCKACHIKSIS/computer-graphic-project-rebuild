#ifndef AUTOREGRESSIVEMOVINGAVERAGEORDERSIGNAL_H
#define AUTOREGRESSIVEMOVINGAVERAGEORDERSIGNAL_H
#include <mainwindow/simulationWindow/basesimulionwindow.h>
#include <vector>
#include <QScrollArea>

class MainWindow;

class AutoregressiveMovingAverageOrderSignal : public BaseSimulionWindow
{
public:
    AutoregressiveMovingAverageOrderSignal(MainWindow *m_wind);
    void simulateSignal();
    void addLinesForBandAValues();

    double frand();
    double getn();

    QLineEdit *p;
    double p_value;

    QLineEdit *q;
    double q_value;

    QLineEdit *q2;
    double q2_value;

    QLineEdit *a_count;
    QLineEdit *b_count;

    std::vector<QLineEdit*> a_values;
    std::vector<QLineEdit*> b_values;

};

#endif // AUTOREGRESSIVEMOVINGAVERAGEORDERSIGNAL_H
