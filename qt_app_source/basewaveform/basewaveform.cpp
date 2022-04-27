#include "basewaveform.h"
#include <qwt_plot_curve.h>
#include <QPolygonF>
#include <QPointF>
#include <QMenu>
#include <qwt_date_scale_draw.h>
#include <qwt_date_scale_engine.h>
#include <qwt_date.h>
#include <iostream>
#include <basewaveform/Splitter/splitter.h>
#include <basewaveform/timescaledraw.h>

BaseWaveForm::BaseWaveForm(CanalOfSignal base, const dataStructure &data_from_file){
    this->foundation = base;
    this->createSimplePlot(data_from_file.period_of_tick, data_from_file);
}

void BaseWaveForm::createSimplePlot( const double &period_of_tick, const dataStructure &data_from_file){

    this->setStyleSheet("border: 1px solid black ;color:black");
    this->createCoordinates(period_of_tick);
    this->enableAxis(QwtPlot::xBottom, false);
    this->enableAxis(QwtPlot::yLeft, false);

    this->setAxisScaleDraw(QwtPlot::xBottom, new TimeScaleDraw);


    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle(this->foundation.name_of_channel.c_str());
    curve->setPen( Qt::blue, 2 );
    QPolygonF points;

    for ( auto coordinate: this->coordinates ){
        points << QPointF(coordinate.first, coordinate.second);
    }

    curve->setSamples( points );
    curve->attach( this );
    this->setContextMenuPolicy(Qt::CustomContextMenu);

}

void BaseWaveForm::clearPlot(){
    return;
}

void BaseWaveForm::createCoordinates(const double &period_of_tick){
    int tick = 1;
    for ( auto y: this->foundation.values_of_signal ){
        this->coordinates.push_back(std::pair(tick * period_of_tick, y));
        tick++;
    }
}

std::vector< std::pair<double, double> >BaseWaveForm:: Coordinates(){
    return this->coordinates;
}

