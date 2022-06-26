#include "spectralcontextmenu.h"
#include <mainwindow/Analis/spectralanalysis.h>

SpectralContextMenu::SpectralContextMenu(SpectralAnalysis *s_a)
{
    this->parent_window = s_a;
    if ( this->parent_window->picker == nullptr ){
        this->set_behavior_picker = new QAction("Включить ослеживание координат", this);
        this->addAction(this->set_behavior_picker);
    }
    else{
        this->set_behavior_picker = new QAction("Выключить отслеживание координат", this);
        this->addAction(this->set_behavior_picker);
    }
    connect(this->set_behavior_picker, &QAction::triggered, this, &SpectralContextMenu::setPickerBehavior);
}

void SpectralContextMenu::setPickerBehavior(){
    this->parent_window->changePickerBehavior();
}
