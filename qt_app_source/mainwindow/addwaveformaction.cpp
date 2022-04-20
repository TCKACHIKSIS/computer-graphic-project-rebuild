#include "addwaveformaction.h"
#include <mainwindow/mainwindow.h>

AddWaveformAction::AddWaveformAction(MainWindow *mainwindow ,const char *name, navigationWaveform &package) : QAction(name)
{
    this->window = mainwindow;
    this->waveform_from_navigate = &package;
    connect(this, &QAction::triggered, this, &AddWaveformAction::addToCentral);
}
void AddWaveformAction::addToCentral(){
    this->window->addWaveformToCentral(*this->waveform_from_navigate);
}
