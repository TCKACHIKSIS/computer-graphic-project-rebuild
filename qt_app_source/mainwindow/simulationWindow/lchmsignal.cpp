#include "lchmsignal.h"
#include <mainwindow/mainwindow.h>
#include <QMessageBox>
#include <math.h>

LCHMSignal::LCHMSignal(MainWindow *m_wind) : BaseSimulionWindow(m_wind)
{
    QLabel *label = new QLabel("Сигнал с линейной частотной модуляцией");
    this->box_layout->addWidget(label);
    label = new QLabel("Введите a");
    this->box_layout->addWidget(label);

    this->a = new QLineEdit();
    this->box_layout->addWidget(this->a);

    label = new QLabel("Введите f0");
    this->box_layout->addWidget(label);

    this->f0 = new QLineEdit();
    this->box_layout->addWidget(this->f0);

    label = new QLabel("Введите fk");
    this->box_layout->addWidget(label);

    this->fk = new QLineEdit();
    this->box_layout->addWidget(this->fk);

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

    this->id = 10;

    connect(this->simulation_button, &QPushButton::released, this, &LCHMSignal::simulateSignal);
}

void LCHMSignal::simulateSignal(){
    this->readBaseParametrs();
    if ( this->main_window->main_data_from_file == nullptr ){
        return;
    }

    if ( this->a->text().size() == 0 || this->f0 == 0 || this->fi->text().size() == 0 || this->fk->text().size() == 0){
        QMessageBox::warning(this, "Ошибка", "Введите необходимую информацию");
        return;
    }

    for ( int i = 1; i <= new_signal->number_of_samples; i++ ){
        this->new_signal->values_of_signal.push_back(
          this->a->text().toDouble() * cos(
                        2 * M_PI * ( this->f0->text().toDouble() + (this->fk->text().toDouble() - this->f0->text().toDouble())/(this->new_signal->sampling_frequency * this->new_signal->period_of_tick) * i * this->new_signal->period_of_tick  )
                        * i * this->new_signal->period_of_tick + this->f0->text().toDouble()
                        )
                    );
    }

    this->main_window->main_data_from_file->signals_channels.push_back(*new_signal);
    navigationWaveform *a = new navigationWaveform(this->main_window->main_data_from_file->signals_channels.back() ,this->main_window);
    a->setTitle(this->main_window->main_data_from_file->signals_channels.back().name_of_channel.c_str());
    a->setMinimumHeight(65);
    this->main_window->navigation_window->widget()->layout()->addWidget(a);

    this->close();
}
