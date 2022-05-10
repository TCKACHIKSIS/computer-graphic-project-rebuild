#include "basesimulionwindow.h"
#include <mainwindow/mainwindow.h>

BaseSimulionWindow::BaseSimulionWindow(MainWindow *mwind)
{
    this->main_window = mwind;
    this->box_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    connect(this->simulation_button, &QPushButton::released, this, &BaseSimulionWindow::simulateSignal);
}
