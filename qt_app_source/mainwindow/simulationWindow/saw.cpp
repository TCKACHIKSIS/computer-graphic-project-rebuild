#include "saw.h"
#include <mainwindow/mainwindow.h>
#include <QMessageBox>

Saw::Saw( MainWindow *m_wind ) : BaseSimulionWindow(m_wind)
{
    QLabel *label = new QLabel("Пила");
    this->box_layout->addWidget(label);
    label = new QLabel("Введите L");
    this->box_layout->addWidget(label);

    this->L = new QLineEdit();
    this->box_layout->addWidget(this->L);

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

    this->id = 6;

    connect(this->simulation_button, &QPushButton::released, this, &Saw::simulateSignal);
}

void Saw::simulateSignal(){
    this->readBaseParametrs();
    if ( this->main_window->main_data_from_file == nullptr ){
        return;
    }

    if ( this->L->text().size() == 0 ){
        QMessageBox::warning(this, "Ошибка", "Введите необходимую информацию");
        return;
    }

    for ( int i = 1; i <= new_signal->number_of_samples; i++ ){
        this->new_signal->values_of_signal.push_back(((double)(i % L->text().toInt())) / L->text().toDouble());
    }

    this->main_window->main_data_from_file->signals_channels.push_back(*new_signal);
    navigationWaveform *a = new navigationWaveform(this->main_window->main_data_from_file->signals_channels.back() ,this->main_window);
    a->setTitle(this->main_window->main_data_from_file->signals_channels.back().name_of_channel.c_str());
    a->setMinimumHeight(65);
    this->main_window->navigation_window->widget()->layout()->addWidget(a);

    this->close();
}
