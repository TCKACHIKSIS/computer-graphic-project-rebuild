#include "centralwaveform.h"
#include <context_menus/centralContextMenu/centralcontextmenu.h>
#include <mainwindow/mainwindow.h>
CentralWaveform::CentralWaveform(CanalOfSignal base, double period_of_tick) : BaseWaveForm(base, period_of_tick)
{

}
void CentralWaveform::mousePressEvent(QMouseEvent *event){
    centralContextMenu *menu = new centralContextMenu(this);
    menu->popup(this->mapToGlobal(event->pos()));
}
