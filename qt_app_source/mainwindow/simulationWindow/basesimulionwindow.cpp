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
    this->main_window->main_data_from_file = new dataStructure();
    this->main_window->main_data_from_file->number_of_channels = 1;
    this->main_window->main_data_from_file->channels_names.push_back("Model_1_1");
    this->main_window->main_data_from_file->number_of_samples = this->number_of_samples->text().toInt();
    this->main_window->main_data_from_file->period_of_tick = 1 / this->sampling_frequency->text().toDouble();
    this->main_window->main_data_from_file->sampling_frequency = this->sampling_frequency->text().toDouble();
    this->main_window->main_data_from_file->signal_start_date = "01-01-2000";
    this->main_window->main_data_from_file->signal_start_time = "00:00:00";



    return;
}

void BaseSimulionWindow::readBaseParametrs(){
    if ( this->main_window->main_data_from_file == nullptr){
        this->createMainSignal();
        return;
    }
    else{
        if ( (this->sampling_frequency->text().size() != 0 && this->sampling_frequency->text().toInt() != this->main_window->main_data_from_file->sampling_frequency) ||
             (this->number_of_samples->text().size() != 0 && this->number_of_samples->text().toInt() != this->main_window->main_data_from_file->number_of_samples)){
            this->main_window->clearMainData();
            this->createMainSignal();
            return;
        }
    }
}


