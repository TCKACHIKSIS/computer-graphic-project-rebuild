#ifndef BASEPLOT_H
#define BASEPLOT_H
#include <qwt_plot.h>
#include "custom_context_menu/baseplotcustromcontextmenu.h"
//unused, delete later
class BasePlot : public QwtPlot
{
public:
    BasePlotCustromContextMenu *qmenu;
    BasePlot();
    virtual void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void requestContextMenu(QPoint a);
};

#endif // BASEPLOT_H
