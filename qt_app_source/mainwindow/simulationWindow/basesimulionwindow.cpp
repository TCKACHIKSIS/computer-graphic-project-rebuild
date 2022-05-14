#include "basesimulionwindow.h"
#include <mainwindow/mainwindow.h>
#include <QMessageBox>

BaseSimulionWindow::BaseSimulionWindow(MainWindow *mwind)
{
    this->main_window = mwind;
    this->box_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);

}

void BaseSimulionWindow::createMainSignal(){

    this->main_window->initialInterfaceSetup();
    this->isRecreateChannel = true;

    if ( this->number_of_samples->text().size() == 0 || this->sampling_frequency->text().size() == 0 ){
            QMessageBox::warning(this, "Внимание", "Введите необходимую информацию");
            return;
    }
    this->main_window->counters_for_simulated_signals[this->id]++;
    this->main_window->main_data_from_file = new dataStructure();
    this->main_window->main_data_from_file->number_of_channels = 1;
    this->main_window->main_data_from_file->channels_names.push_back("Model_" + std::to_string(this->id) + "_" + std::to_string(this->main_window->counters_for_simulated_signals[this->id]));
    this->main_window->main_data_from_file->number_of_samples = this->number_of_samples->text().toInt();
    this->main_window->main_data_from_file->period_of_tick = 1 / this->sampling_frequency->text().toDouble();
    this->main_window->main_data_from_file->sampling_frequency = this->sampling_frequency->text().toDouble();
    this->main_window->main_data_from_file->signal_start_date = "01-01-2000";
    this->main_window->main_data_from_file->signal_start_time = "00:00:00";

    this->new_signal = new CanalOfSignal();
    new_signal->name_of_channel = this->main_window->main_data_from_file->channels_names.back();
    new_signal->number_of_samples = this->main_window->main_data_from_file->number_of_samples;
    new_signal->period_of_tick = this->main_window->main_data_from_file->period_of_tick;
    new_signal->recording_duration = this->main_window->main_data_from_file->recording_duration;
    new_signal->sampling_frequency = this->main_window->main_data_from_file->sampling_frequency;
    new_signal->source_of_channel = "Моделирование";
    return;
}

void BaseSimulionWindow::complementMainSignal(){
    this->main_window->main_data_from_file->number_of_channels++;
    this->main_window->counters_for_simulated_signals[this->id]++;
    this->main_window->main_data_from_file->channels_names.push_back("Model_" + std::to_string(this->id) + "_" + std::to_string(this->main_window->counters_for_simulated_signals[this->id]));

    this->new_signal = new CanalOfSignal();
    new_signal->name_of_channel = this->main_window->main_data_from_file->channels_names.back();
    new_signal->number_of_samples = this->main_window->main_data_from_file->number_of_samples;
    new_signal->period_of_tick = this->main_window->main_data_from_file->period_of_tick;
    new_signal->recording_duration = this->main_window->main_data_from_file->recording_duration;
    new_signal->sampling_frequency = this->main_window->main_data_from_file->sampling_frequency;
    new_signal->source_of_channel = "Моделирование";

}

void BaseSimulionWindow::readBaseParametrs(){
    if ( this->main_window->main_data_from_file == nullptr){
        this->createMainSignal();
        return;
    }
    else{
        if ( (this->sampling_frequency->text().size() != 0 && this->sampling_frequency->text().toDouble() != this->main_window->main_data_from_file->sampling_frequency) ||
             (this->number_of_samples->text().size() != 0 && this->number_of_samples->text().toInt() != this->main_window->main_data_from_file->number_of_samples)){
            this->main_window->clearMainData();
            this->createMainSignal();
            return;
        }
        else {
            this->complementMainSignal();
            return;
        }
    }
}


