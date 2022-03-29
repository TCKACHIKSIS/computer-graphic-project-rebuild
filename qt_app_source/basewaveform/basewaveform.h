#ifndef BASEWAVEFORM_H
#define BASEWAVEFORM_H
#include <base_plot/baseplot.h>
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
    BasePlot *plot;
    std::vector< std::pair<double, double> > Coordinates();
    CanalOfSignal *foundation;
    BaseWaveForm();
    void createSimplePlot();
    void clearPlot();
    void createCoordinates(CanalOfSignal &base, const double &period_of_tick);

signals:

};

#endif // BASEWAVEFORM_H
