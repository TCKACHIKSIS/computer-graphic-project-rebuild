#include "navigationcontextmenu.h"
#include <iostream>

NavigationContextMenu::NavigationContextMenu(navigationWaveform *parent_plot)
{
    this->parentPlot = parent_plot;
    this->add_waveform = new QAction("Осцилограмма", this);
    this->addAction(this->add_waveform);
    connect(this->add_waveform, &QAction::triggered, this, &NavigationContextMenu::addWaveformEmit );
}
