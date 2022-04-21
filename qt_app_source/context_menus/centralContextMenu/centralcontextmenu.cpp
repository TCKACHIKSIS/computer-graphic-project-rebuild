#include "centralcontextmenu.h"

centralContextMenu::centralContextMenu(CentralWaveform *parent_plot)
{
    this->parentplot = parent_plot;
    this->delete_waveform = new QAction("Удалить", this);
    this->addAction(this->delete_waveform);
    connect(this->delete_waveform, &QAction::triggered, this, &centralContextMenu::deleteWaveformFromeCentral );
}

void centralContextMenu::deleteWaveformFromeCentral(){
    this->parentplot->~CentralWaveform();
}
