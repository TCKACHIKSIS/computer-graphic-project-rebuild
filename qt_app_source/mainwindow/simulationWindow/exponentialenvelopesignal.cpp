#include "exponentialenvelopesignal.h"
#include <mainwindow/mainwindow.h>
#include <QMessageBox>
#include <math.h>

ExponentialEnvelopeSignal::ExponentialEnvelopeSignal(MainWindow *m_wind) : BaseSimulionWindow(m_wind)
{
    QLabel *label = new QLabel("сигнал с экспоненциальной огибающей");
    this->box_layout->addWidget(label);

    label = new QLabel("Введите a");
    this->box_layout->addWidget(label);

    this->a = new QLineEdit();
    this->box_layout->addWidget(this->a);

    label = new QLabel("Введите тау");
    this->box_layout->addWidget(label);

    this->tau = new QLineEdit();
    this->box_layout->addWidget(this->tau);

    label = new QLabel("Введите f");
    this->box_layout->addWidget(label);

    this->f = new QLineEdit();
    this->box_layout->addWidget(this->f);

    label = new QLabel("Введите fi");
    this->box_layout->addWidget(label);

    this->fi = new QLineEdit();
    this->box_layout->addWidget(this->fi);

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

    this->id = 7;

    connect(this->simulation_button, &QPushButton::released, this, &ExponentialEnvelopeSignal::simulateSignal);
}

void ExponentialEnvelopeSignal::simulateSignal(){
    this->readBaseParametrs();
    if ( this->main_window->main_data_from_file == nullptr ){
        return;
    }

    if ( this->a->text().size() == 0 || this->f->text().size() == 0 || this->fi->text().size() == 0 || this->tau->text().size() == 0){
        QMessageBox::warning(this, "Ошибка", "Введите необходимую информацию");
        return;
    }

    if ( this->f->text().toDouble() > 0.5*this->new_signal->sampling_frequency || this->f->text().toDouble() < 0 ){
         QMessageBox::warning(this, "Ошибка", "Неверное f");
         return;
     }

    for ( int i = 1; i <= new_signal->number_of_samples; i++ ){
        this->new_signal->values_of_signal.push_back(
          this->a->text().toDouble() * exp(-i*this->new_signal->period_of_tick) * cos(2*M_PI*this->f->text().toDouble()
                                      * i*this->new_signal->period_of_tick + this->fi->text().toDouble())
                    );
    }

    this->main_window->main_data_from_file->signals_channels.push_back(*new_signal);
    navigationWaveform *a = new navigationWaveform(this->main_window->main_data_from_file->signals_channels.back() ,this->main_window);
    a->setTitle(this->main_window->main_data_from_file->signals_channels.back().name_of_channel.c_str());
    a->setMinimumHeight(65);
    this->main_window->navigation_window->widget()->layout()->addWidget(a);

    this->close();
}
