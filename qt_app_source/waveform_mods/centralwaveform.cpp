#include "centralwaveform.h"
#include <context_menus/centralContextMenu/centralcontextmenu.h>
#include <mainwindow/mainwindow.h>
#include <algorithm>
CentralWaveform::CentralWaveform(CanalOfSignal base, const dataStructure &data_from_file) : BaseWaveForm(base, data_from_file)
{

    this->enableAxis(QwtPlot::xBottom, true);
    this->enableAxis(QwtPlot::yLeft, true);

    /*
    this->magnifier = new QwtPlotMagnifier(this->canvas());
    this->magnifier->setMouseButton(Qt::MiddleButton);

    this->panner = new QwtPlotPanner(this->canvas());
    this->panner->setMouseButton(Qt::LeftButton);
    */

    this->zoomer = new QwtPlotZoomer(this->canvas());
    this->zoomer->setRubberBandPen(QPen(Qt::white));
}
void CentralWaveform::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton){
        centralContextMenu *menu = new centralContextMenu(this);
        menu->popup(this->mapToGlobal(event->pos()));
    }
}

void CentralWaveform::changePickerBehavior(){
    if ( this->picker == nullptr ){
        this->picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
                                         this->canvas());
        QPen *pen = new QPen(Qt::red);
        pen->setWidth(2);
        this->picker->setRubberBandPen(*pen);
        this->picker->setTrackerPen( QPen( Qt::black ) );
        this->picker->setStateMachine( new QwtPickerTrackerMachine );
    }
    else {
        delete this->picker;
        this->picker = nullptr;
    }
}

void CentralWaveform::enableAxisesFromContext(){
    this->enableAxis(QwtPlot::xBottom, !this->axisEnabled(QwtPlot::xBottom));
    this->enableAxis(QwtPlot::yLeft, !this->axisEnabled(QwtPlot::yLeft));
}

void CentralWaveform::changeMarkersVision(){
    if ( this->markers == nullptr ){
        this->markers = new QwtSymbol( QwtSymbol::Ellipse,
                                   QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        this->curve->setSymbol(this->markers);
        this->replot();
    }
    else{
        this->curve->setSymbol(nullptr);
        this->markers = nullptr;
        this->replot();

    }

}

void CentralWaveform::setLocalScale(){
    std::cout << "ok1" << std::endl;
   if ( this->mainWindow->current_scale_central_waveform->first == 0 && this->mainWindow->current_scale_central_waveform->second == 0){
        this->setGlobalScale();
    }
    std::cout << "ok2" << std::endl;
    auto scale_y_min = std::max_element(this->foundation.values_of_signal.begin(), this->foundation.values_of_signal.end());
    auto scale_y_max = std::min_element(this->foundation.values_of_signal.begin(), this->foundation.values_of_signal.end());
    this-> setAxisScale(QwtPlot::yLeft, *scale_y_max, *scale_y_min);
    this->replot();
}

void CentralWaveform::setGlobalScale(){
    auto scale_y_min = std::max_element(this->foundation.values_of_signal.begin(), this->foundation.values_of_signal.end());
    auto scale_y_max = std::min_element(this->foundation.values_of_signal.begin(), this->foundation.values_of_signal.end());
    this-> setAxisScale(QwtPlot::yLeft, *scale_y_max, *scale_y_min);
    this->replot();
}
