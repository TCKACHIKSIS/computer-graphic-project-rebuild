#include "baseplot.h"
#include <QDebug>
#include <QMouseEvent>

BasePlot::BasePlot()
{

}
void BasePlot::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        qDebug() << "rClicked";

        this->requestContextMenu(event->pos());
    }
}

void BasePlot::requestContextMenu(QPoint a){
    this->qmenu = new BasePlotCustromContextMenu();
    qmenu->popup(a);
}
