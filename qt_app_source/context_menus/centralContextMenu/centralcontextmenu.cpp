#include "centralcontextmenu.h"
#include <iostream>
centralContextMenu::centralContextMenu(CentralWaveform *parent_plot)
{
    this->parentplot = parent_plot;

    this->local_scale = new QAction("Локальное масштабирование");
    this->addAction(this->local_scale);

    this->global_scale = new QAction("Глобальное масштабирование");
    this->addAction(this->global_scale);

    this->set_scale = new QAction("Установить масштабирование");
    this->addAction(this->set_scale);

    this->single_local_scale = new QAction("Единое локальное масштабирвоание");
    this->addAction(this->single_local_scale);

    this->single_global_scale = new QAction("Единое глобальное масштабирование");
    this->addAction(this->single_global_scale);

    this->addSeparator();

    if ( this->parentplot->picker == nullptr ){
        this->set_behavior_picker = new QAction("Включить ослеживание координат", this);
        this->addAction(this->set_behavior_picker);
    }
    else{
        this->set_behavior_picker = new QAction("Выключить отслеживание координат", this);
        this->addAction(this->set_behavior_picker);
    }

    if (this->parentplot->axisEnabled(QwtPlot::yLeft)){
        this->enable_axis = new QAction("Выключить отображение осей");
        this->addAction(this->enable_axis);
    }
    else {
        this->enable_axis = new QAction("Включить отображение осей");
        this->addAction(this->enable_axis);
    }

    if ( this->parentplot->markers == nullptr ){
        this->set_curve_markers = new QAction("Включить маркеры точек");
        this->addAction(this->set_curve_markers);
    }
    else {
        this->set_curve_markers = new QAction("Выключить маркеры точек");
        this->addAction(this->set_curve_markers);
    }

    this->delete_waveform = new QAction("Удалить", this);
    this->addAction(this->delete_waveform);

    connect(this->delete_waveform, &QAction::triggered, this, &centralContextMenu::deleteWaveformFromeCentral );
    connect(this->set_behavior_picker, &QAction::triggered, this, &centralContextMenu::setPickerBehavior);
    connect(this->enable_axis, &QAction::triggered, this, &centralContextMenu::enableAxises);
    connect(this->set_curve_markers, &QAction::triggered, this, &centralContextMenu::setMarkers);
    connect(this->local_scale, &QAction::triggered, this, &centralContextMenu::setLocalScale);
    connect(this->global_scale, &QAction::triggered, this, &centralContextMenu::setGlobalScale);
}

void centralContextMenu::deleteWaveformFromeCentral(){
    this->parentplot->~CentralWaveform();
}

void centralContextMenu::setPickerBehavior(){
    this->parentplot->changePickerBehavior();
}

void centralContextMenu::enableAxises(){
    this->parentplot->enableAxisesFromContext();
}

void centralContextMenu::setMarkers(){
    this->parentplot->changeMarkersVision();
}

void centralContextMenu::setLocalScale(){
    this->parentplot->setLocalScale();
}

void centralContextMenu::setGlobalScale(){
    this->parentplot->setGlobalScale();
}
