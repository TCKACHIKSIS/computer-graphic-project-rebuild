#include "delayedsinglepulsewindow.h"
#include <QLabel>
#include <filehandler/dataStructure.h>
#include <mainwindow/mainwindow.h>
#include <QMessageBox>
#include <mainwindow/addwaveformaction.h>

DelayedSinglePulseWindow::DelayedSinglePulseWindow(MainWindow *mwind) : BaseSimulionWindow(mwind)
{
    QLabel *label = new QLabel("Задержанный единичный импульс");
    this->box_layout->addWidget(label);
    label = new QLabel("Введите n0");
    this->box_layout->addWidget(label);

    this->n_0 = new QLineEdit();
    this->box_layout->addWidget(this->n_0);

    label = new QLabel("Введите количество отсчетов");
    this->box_layout->addWidget(label);

    this->number_of_samples = new QLineEdit();
    this->box_layout->addWidget(this->number_of_samples);

    label = new QLabel("Введите частоту сигнала");
    this->box_layout->addWidget(label);

    this->sampling_frequency = new QLineEdit();
    this->box_layout->addWidget(this->sampling_frequency);

    this->simulation_button = new QPushButton("OK");
    this->box_layout->addWidget(this->simulation_button);

    this->id = 1;

    connect(this->simulation_button, &QPushButton::released, this, &DelayedSinglePulseWindow::simulateSignal);

}
void DelayedSinglePulseWindow::simulateSignal(){

    this->readBaseParametrs();
    if ( this->main_window->main_data_from_file == nullptr ){
        return;
    }

    if ( this->n_0->text().size() == 0 ){
        QMessageBox::warning(this, "Ошибка", "Введите необходимую информацию");
        return;
    }

    for ( int i = 1; i <= new_signal->number_of_samples; i++ ){
        if ( i == this->n_0->text().toInt() ){
            new_signal->values_of_signal.push_back(1);
        }
        else{
            new_signal->values_of_signal.push_back(0);
        }
    }

    this->main_window->main_data_from_file->signals_channels.push_back(*new_signal);
    navigationWaveform *a = new navigationWaveform(this->main_window->main_data_from_file->signals_channels.back() ,this->main_window);
    a->setTitle(this->main_window->main_data_from_file->signals_channels.back().name_of_channel.c_str());
    a->setMinimumHeight(65);
    this->main_window->navigation_window->widget()->layout()->addWidget(a);

    this->close();
}

