#include "delayedsinglepulsewindow.h"
#include <QLabel>
#include <filehandler/dataStructure.h>
#include <mainwindow/mainwindow.h>


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

    CanalOfSignal *new_canal = new CanalOfSignal();
    this->main_window->counting_simulated_signals["DelayedSinglePulse"]++;
    new_canal->name_of_channel = "Model_1_" + std::to_string(this->main_window->counting_simulated_signals["DelayedSinglePulse"]);
    new_canal->source_of_channel = "Смоделированный канал";
    for ( int i = 0; i < this->new_signal->number_of_samples; i++ ){
        if ( i == this->n_0->text().toInt() ){
            new_canal->values_of_signal.push_back(1);
        }
        else{
            new_canal->values_of_signal.push_back(0);
        }
    }
    this->new_signal->signals_channels.push_back(*new_canal);

    navigationWaveform *a = new navigationWaveform(*new_canal, *this->new_signal, this->main_window);
    a->setTitle(new_canal->name_of_channel.c_str());
    a->setMinimumHeight(65);
    this->main_window->navigation_window->widget()->layout()->addWidget(a);
    this->main_window->simulated_signals.push_back(*this->new_signal);

    //AddWaveformAction *waveform_add_action = new AddWaveformAction(this, channel.name_of_channel.c_str(), *a);
    //this->main_window->ui->waveforms->addAction(waveform_add_action);
    this->close();
}

