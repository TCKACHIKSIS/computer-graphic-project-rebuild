#include "whitenoisenormallaw.h"
#include <mainwindow/mainwindow.h>
#include <QMessageBox>

WhiteNoiseNormalLaw::WhiteNoiseNormalLaw(MainWindow *m_wind) : BaseSimulionWindow(m_wind)
{
    QLabel *label = new QLabel("Белый шум, распределенный по нормальному закону");
    this->box_layout->addWidget(label);

    label = new QLabel("Введите a");
    this->box_layout->addWidget(label);

    this->a = new QLineEdit();
    this->box_layout->addWidget(a);

    label = new QLabel("Введите q^2");
    this->box_layout->addWidget(label);

    this->q2 = new QLineEdit();
    this->box_layout->addWidget(q2);

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

    this->id = 12;

    connect(this->simulation_button, &QPushButton::released, this, &WhiteNoiseNormalLaw::simulateSignal);

}

double WhiteNoiseNormalLaw::frand(){
    return (double) rand()/RAND_MAX;
}

double WhiteNoiseNormalLaw::getn(){
    double n = 0;
    for ( int i = 1; i <=12; i++ ){
        n += this->frand();
    }
    n -= 6;
    return n;
}

void WhiteNoiseNormalLaw::simulateSignal(){
    this->readBaseParametrs();
    if ( this->main_window->main_data_from_file == nullptr ){
        return;
    }

    if ( this->a->text().size() == 0 || this->q2->text().size() == 0 ){
        QMessageBox::warning(this, "Ошибка", "Введите необходимую информацию");
        return;
    }

    for ( int i = 1; i <= new_signal->number_of_samples; i++ ){
        this->new_signal->values_of_signal.push_back(
                    this->a->text().toDouble() + sqrt(this->q2->text().toDouble()) * this->getn()
                    );
    }

    this->main_window->main_data_from_file->signals_channels.push_back(*new_signal);
    navigationWaveform *a = new navigationWaveform(this->main_window->main_data_from_file->signals_channels.back() ,this->main_window);
    a->setTitle(this->main_window->main_data_from_file->signals_channels.back().name_of_channel.c_str());
    a->setMinimumHeight(65);
    this->main_window->navigation_window->widget()->layout()->addWidget(a);

    this->close();

}
