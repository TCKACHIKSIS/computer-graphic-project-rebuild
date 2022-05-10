#include "delayedsinglepulsewindow.h"
#include <QLabel>

DelayedSinglePulseWindow::DelayedSinglePulseWindow(MainWindow *mwind) : BaseSimulionWindow(mwind)
{
    QLabel *label = new QLabel("Задержанный единичный импульс");
    this->box_layout->addWidget(label);
    label = new QLabel("Введите n0");
    this->box_layout->addWidget(label);

    this->n_0 = new QLineEdit();
    this->box_layout->addWidget(this->n_0);

    this->simulation_button = new QPushButton("OK");
    this->box_layout->addWidget(this->simulation_button);
}
