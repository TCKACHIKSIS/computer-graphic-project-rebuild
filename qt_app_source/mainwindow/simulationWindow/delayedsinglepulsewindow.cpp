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

    connect(this->simulation_button, &QPushButton::released, this, &DelayedSinglePulseWindow::simulateSignal);

}
void DelayedSinglePulseWindow::simulateSignal(){

    this->readBaseParametrs();

    if ( this->n_0->text().size() == 0 ){
        QMessageBox::warning(this, "Внимание", "Введите необходимую информацию");
        return;
    }
    std::cout << "ok" << std::endl;
    this->new_signal = new CanalOfSignal();
    new_signal->name_of_channel = this->main_window->main_data_from_file->channels_names.back();
    new_signal->number_of_samples = this->main_window->main_data_from_file->number_of_samples;
    new_signal->period_of_tick = this->main_window->main_data_from_file->period_of_tick;
    new_signal->recording_duration = this->main_window->main_data_from_file->recording_duration;
    new_signal->sampling_frequency = this->main_window->main_data_from_file->sampling_frequency;
    new_signal->source_of_channel = "Моделирование";

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

