#include "basewaveform.h"
#include <QPolygonF>
#include <QPointF>
#include <QMenu>
#include <qwt_date_scale_draw.h>
#include <qwt_date_scale_engine.h>
#include <qwt_date.h>
#include <iostream>
#include <basewaveform/Splitter/splitter.h>
#include <basewaveform/timescaledraw.h>

BaseWaveForm::BaseWaveForm(CanalOfSignal base){
    this->foundation = base;
    this->createSimplePlot();
}

void BaseWaveForm::createSimplePlot(){

    this->setStyleSheet("border: 1px solid black ;color:black");
    this->createCoordinates(this->foundation.period_of_tick);
    this->enableAxis(QwtPlot::xBottom, false);
    this->enableAxis(QwtPlot::yLeft, false);
    this->grid_on_plot = new QwtPlotGrid();
    this->grid_on_plot->setMajorPen(Qt::gray);
    this->grid_on_plot->attach(this);

    this->setAxisScaleDraw(QwtPlot::xBottom, new TimeScaleDraw);


    this->curve = new QwtPlotCurve();
    this->curve->setTitle(this->foundation.name_of_channel.c_str());
    this->curve->setPen( Qt::blue, 2 );
    QPolygonF points;

    for ( auto coordinate: this->coordinates ){
        points << QPointF(coordinate.first, coordinate.second);
    }

    this->curve->setSamples( points );
    this->curve->attach( this );
    this->setContextMenuPolicy(Qt::CustomContextMenu);

}

void BaseWaveForm::clearPlot(){
    return;
}

void BaseWaveForm::createCoordinates(const double &period_of_tick){
    int tick = 1;
    for ( auto y: this->foundation.values_of_signal ){
        this->coordinates.push_back(std::pair(tick * this->foundation.period_of_tick, y));
        tick++;
    }
}

std::vector< std::pair<double, double> >BaseWaveForm:: Coordinates(){
    return this->coordinates;
}

