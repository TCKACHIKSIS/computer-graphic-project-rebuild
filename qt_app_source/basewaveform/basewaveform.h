#ifndef BASEWAVEFORM_H
#define BASEWAVEFORM_H
#include <qwt_plot.h>
#include <QWidget>
#include <canalofsignal/canalofsignal.h>
#include <utility>
#include <vector>

#include <canalofsignal/canalofsignal.h>

class BaseWaveForm
{
private:
    std::vector< std::pair<double, double> > coordinates;
public:
    QwtPlot *plot;
    std::vector< std::pair<double, double> > Coordinates();

    BaseWaveForm();
    void createSimplePlot();
    void clearPlot();
    void createCoordinates(const CanalOfSignal &base, const double &period_of_tick);

signals:

};

#endif // BASEWAVEFORM_H
