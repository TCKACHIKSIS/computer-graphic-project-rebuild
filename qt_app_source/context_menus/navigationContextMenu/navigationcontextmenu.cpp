#include "navigationcontextmenu.h"
#include <iostream>
#include <mainwindow/mainwindow.h>

NavigationContextMenu::NavigationContextMenu(navigationWaveform *parent_plot)
{
    this->parentPlot = parent_plot;
    this->add_waveform = new QAction("Осцилограмма", this);
    this->addAction(this->add_waveform);
    connect(this->add_waveform, &QAction::triggered, this, &NavigationContextMenu::addWaveformEmit );
}
void NavigationContextMenu::addWaveformEmit(){
    this->parentPlot->add_wave_form_was_clicked();
}

