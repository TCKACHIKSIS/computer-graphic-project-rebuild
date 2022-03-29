#include "basewaveform.h"
#include <qwt_plot_curve.h>
#include <QPolygonF>
#include <QPointF>
BaseWaveForm::BaseWaveForm(){
    return;
}

void BaseWaveForm::createSimplePlot(){
    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle(this->foundation->name_of_channel.c_str());
    curve->setPen( Qt::blue, 2 );
    curve->setTitle( "Demo Curve" );
    QPolygonF points;
    for ( auto coordinate: this->coordinates ){
        points << QPointF(coordinate.first, coordinate.second);
    }
    curve->setSamples( points );
    curve->attach( this->plot );
}

void BaseWaveForm::clearPlot(){
    return;
}

void BaseWaveForm::createCoordinates(CanalOfSignal &base, const double &period_of_tick){
    int tick = 1;
    this->foundation = &base;
    for ( auto y: base.values_of_signal ){
        this->coordinates.push_back(std::pair(tick * period_of_tick, y));
        tick++;
    }
}

std::vector< std::pair<double, double> >BaseWaveForm:: Coordinates(){
    return this->coordinates;
}
