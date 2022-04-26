#include "navigationwaveform.h"
#include <context_menus/navigationContextMenu/navigationcontextmenu.h>
#include <mainwindow/mainwindow.h>
navigationWaveform::navigationWaveform(CanalOfSignal base, const dataStructure &data_from_file, MainWindow *mwind) : BaseWaveForm(base, data_from_file)
{
    this->mainWindow = mwind;
    return;
}
void navigationWaveform::mousePressEvent(QMouseEvent *event){

    NavigationContextMenu *menu = new NavigationContextMenu(this);
    menu->popup(this->mapToGlobal(event->pos()));
}

void navigationWaveform::add_wave_form_was_clicked(){
    this->mainWindow->addWaveformToCentral(*this);

}
