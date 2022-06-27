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

    if ( this->parent_window->markers == nullptr ){
        this->set_markers_vision = new QAction("Включить маркеры", this);
        this->addAction(this->set_markers_vision);
    }
    else{
        this->set_markers_vision = new QAction("Выключить маркеры", this);
        this->addAction(this->set_markers_vision);
    }

    connect(this->set_behavior_picker, &QAction::triggered, this, &SpectralContextMenu::setPickerBehavior);
    connect(this->set_markers_vision, &QAction::triggered, this, &SpectralContextMenu::setMarkersVision);
}

void SpectralContextMenu::setPickerBehavior(){
    this->parent_window->changePickerBehavior();
}

void SpectralContextMenu::setMarkersVision(){
    this->parent_window->changeMarkersVision();
}
