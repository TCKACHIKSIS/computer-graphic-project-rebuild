#include "centralwaveform.h"
#include <context_menus/centralContextMenu/centralcontextmenu.h>
#include <mainwindow/mainwindow.h>
CentralWaveform::CentralWaveform(CanalOfSignal base, const dataStructure &data_from_file) : BaseWaveForm(base, data_from_file)
{

    this->enableAxis(QwtPlot::xBottom, true);
    this->enableAxis(QwtPlot::yLeft, true);

    this->magnifier = new QwtPlotMagnifier(this->canvas());
    this->magnifier->setMouseButton(Qt::MiddleButton);

    this->panner = new QwtPlotPanner(this->canvas());
    this->panner->setMouseButton(Qt::LeftButton);

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
