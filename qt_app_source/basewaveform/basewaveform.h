#ifndef BASEWAVEFORM_H
#define BASEWAVEFORM_H
#include <QWidget>
#include <canalofsignal/canalofsignal.h>
#include <utility>
#include <vector>
#include <qwt_plot.h>
#include <QMouseEvent>

#include <canalofsignal/canalofsignal.h>
#include <filehandler/dataStructure.h>

class BaseWaveForm : public QwtPlot
{

private:
    std::vector< std::pair<double, double> > coordinates;
public:
    std::vector< std::pair<double, double> > Coordinates();
    CanalOfSignal foundation;
    dataStructure *data_from_file;
    BaseWaveForm(CanalOfSignal base, const dataStructure &data_from_file);
    void createSimplePlot(const double &period_of_tick, const dataStructure &data_from_file);
    void clearPlot();
    void createCoordinates(const double &period_of_tick);

};

#endif // BASEWAVEFORM_H
