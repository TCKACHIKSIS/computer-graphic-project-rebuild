#include "autoregressivemovingaverageordersignal.h"
#include <mainwindow/mainwindow.h>
#include <QMessageBox>

AutoregressiveMovingAverageOrderSignal::AutoregressiveMovingAverageOrderSignal(MainWindow *m_wind) : BaseSimulionWindow(m_wind)
{
    QLabel *label = new QLabel("Сигнал авторегрессии скользящего среднего порядка");
    this->box_layout->addWidget(label);

    label = new QLabel("Введите p");
    this->box_layout->addWidget(label);

    this->p = new QLineEdit();
    this->box_layout->addWidget(p);

    label = new QLabel("Введите q");
    this->box_layout->addWidget(label);

    this->q = new QLineEdit();
    this->box_layout->addWidget(q);

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

    this->id = 13;

    connect(this->simulation_button, &QPushButton::released, this, &AutoregressiveMovingAverageOrderSignal::simulateSignal);
}

double AutoregressiveMovingAverageOrderSignal::frand(){
    return (double) rand()/RAND_MAX;
}

double AutoregressiveMovingAverageOrderSignal::getn(){
    double n = 0;
    for ( int i = 1; i <=12; i++ ){
        n += this->frand();
    }
    n -= 6;
    return n;
}

void AutoregressiveMovingAverageOrderSignal::simulateSignal(){
    this->readBaseParametrs();
    if ( this->main_window->main_data_from_file == nullptr ){
        return;
    }

    if ( this->p->text().size() == 0 || this->q->text().size() == 0 ){
        QMessageBox::warning(this, "Ошибка", "Введите необходимую информацию");
        return;
    }

    for ( int i = 1; i <= new_signal->number_of_samples; i++ ){
        double x0 = sqrt(this->q2->text().toDouble()) * this->getn();
    }

}
