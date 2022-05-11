#include "basesimulionwindow.h"
#include <mainwindow/mainwindow.h>

BaseSimulionWindow::BaseSimulionWindow(MainWindow *mwind)
{
    this->main_window = mwind;
    this->box_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);

}

void clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void BaseSimulionWindow::readBaseParametrs(){
    //это п***здец
    this->new_signal = new dataStructure();

    if ( this->number_of_samples->text().size() == 0 ){
        if ( this->main_window->main_data_from_file != nullptr ){
            this->new_signal->number_of_samples = this->main_window->main_data_from_file->number_of_samples;
        }
        else{
            this->new_signal->number_of_samples = 1000;
        }
    }
    else{
        this->new_signal->number_of_samples = this->number_of_samples->text().toInt();
    }

    if ( this->sampling_frequency->text().size() == 0 ){
        if ( this->main_window->main_data_from_file != nullptr ){
            this->new_signal->sampling_frequency = this->main_window->main_data_from_file->sampling_frequency;
        }
        else{
            this->new_signal->sampling_frequency = 1;
            this->new_signal->period_of_tick = 1;
        }
    }
    else{
        this->new_signal->sampling_frequency = this->number_of_samples->text().toDouble();
        this->new_signal->period_of_tick = 1 / this->new_signal->sampling_frequency;
    }

    if ( this->main_window->main_data_from_file != nullptr &&
         ( this->new_signal->number_of_samples != this->main_window->main_data_from_file->number_of_samples ||
           this->new_signal->sampling_frequency != this->main_window->main_data_from_file->sampling_frequency) ){
        this->new_signal->signal_start_date = "01-01-2000";
        this->new_signal->signal_start_time = "00:00:00";
    }
    else if ( this->main_window->main_data_from_file != nullptr ){
        this->new_signal->signal_start_date = this->main_window->main_data_from_file->signal_start_date;
        this->new_signal->signal_start_time = this->main_window->main_data_from_file->signal_start_time;
    }
    clearLayout(this->main_window->navigation_window->widget()->layout());
    delete(this->main_window->main_data_from_file);
    this->main_window->main_data_from_file = nullptr;
}
