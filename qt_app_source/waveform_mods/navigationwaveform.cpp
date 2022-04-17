#include "navigationwaveform.h"
#include <context_menus/navigationContextMenu/navigationcontextmenu.h>
#include <iostream>
navigationWaveform::navigationWaveform(MainWindow *papasha)
{
    this->mainWindow = papasha;
}
void navigationWaveform::mousePressEvent(QMouseEvent *event){

    NavigationContextMenu *menu = new NavigationContextMenu(this);
    menu->popup(this->mapToGlobal(event->pos()));
}
void navigationWaveform::add_wave_form_was_clicked(){
    this->mainWindow->addWaveformToCentral(this);
}
