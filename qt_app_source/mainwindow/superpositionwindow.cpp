#include "superpositionwindow.h"
#include <mainwindow/mainwindow.h>
#include <QButtonGroup>

SuperPositionWindow::SuperPositionWindow( MainWindow *m_wind )
{
    this->main_window = m_wind;
    this->box_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    QLabel *label = new QLabel("Выберите каналы для составления суперпозиции");
    this->box_layout->addWidget(label);

    for ( auto channel: this->main_window->main_data_from_file->signals_channels ){
        /* CheckBoxForChannels *ptr = new CheckBoxForChannels(channel.name_of_channel.c_str(), channel, this);
        this->box_layout->addWidget(ptr);
        this->check_box_list.push_back(ptr);

        std::string ptr_label = "Коэффициент для " + channel.name_of_channel;
        label = new QLabel(ptr_label.c_str());

        QLineEdit *line_edit = new QLineEdit();
        this->box_layout->addWidget(line_edit);
        */
        CheckBoxForChannelsAndLineEditForCoef *ptr = new CheckBoxForChannelsAndLineEditForCoef();
        ptr->line_edit = new QLineEdit();
        ptr->check_box = new CheckBoxForChannels(channel.name_of_channel.c_str(), channel, this);
        this->check_box_list.push_back(ptr);

        this->box_layout->addWidget(ptr->check_box);

        std::string ptr_label = "Коэффициент для " + channel.name_of_channel;
        label = new QLabel(ptr_label.c_str());
        this->box_layout->addWidget(label);

        this->box_layout->addWidget(ptr->line_edit);
    }

    this->create_superposition_button = new QPushButton("OK");
    this->box_layout->addWidget(this->create_superposition_button);

    this->multiplication = new QCheckBox("Произведение");
    this->addition = new QCheckBox("Сумма");

    QButtonGroup *button_group = new QButtonGroup(this);
    button_group->setExclusive(true);
    button_group->addButton(this->multiplication);
    button_group->addButton(this->addition);

    this->box_layout->addWidget(this->multiplication);
    this->box_layout->addWidget(this->addition);

    connect(this->create_superposition_button, &QPushButton::released, this, &SuperPositionWindow::createSuperposition);

}

void SuperPositionWindow::createSuperposition(){
    CanalOfSignal *superposition_channel = new CanalOfSignal();
    this->main_window->main_data_from_file->number_of_channels++;

    superposition_channel->number_of_samples = this->main_window->main_data_from_file->number_of_samples;
    superposition_channel->period_of_tick = this->main_window->main_data_from_file->period_of_tick;
    superposition_channel->recording_duration = this->main_window->main_data_from_file->recording_duration;
    superposition_channel->sampling_frequency = this->main_window->main_data_from_file->sampling_frequency;
    superposition_channel->source_of_channel = "Суперпозиция";
    superposition_channel->name_of_channel = "Суперпозиция";
    this->main_window->main_data_from_file->channels_names.push_back(superposition_channel->name_of_channel);

    for ( CheckBoxForChannelsAndLineEditForCoef *lineedit_and_checkbox: this->check_box_list ){
        if ( lineedit_and_checkbox->check_box->checkState() ){

            if ( superposition_channel->values_of_signal.empty() ){
                for ( auto value: lineedit_and_checkbox->check_box->canal.values_of_signal ){
                    superposition_channel->values_of_signal.push_back(value * lineedit_and_checkbox->line_edit->text().toDouble());
                }
            }

            else {

                if ( this->addition->checkState() ){
                    for ( int i = 0; i < superposition_channel->number_of_samples; i++ ){
                        superposition_channel->values_of_signal[i] = superposition_channel->values_of_signal[i]
                            + lineedit_and_checkbox->check_box->canal.values_of_signal[i] * lineedit_and_checkbox->line_edit->text().toDouble();
                    }
                }

                if ( this->multiplication->checkState() ){
                    for ( int i = 0; i < superposition_channel->number_of_samples; i++ ){
                        superposition_channel->values_of_signal[i] = superposition_channel->values_of_signal[i]
                            * lineedit_and_checkbox->check_box->canal.values_of_signal[i];
                    }
                }
            }
        }
    }

    this->main_window->main_data_from_file->signals_channels.push_back(*superposition_channel);
    navigationWaveform *a = new navigationWaveform(this->main_window->main_data_from_file->signals_channels.back() ,this->main_window);
    a->setTitle(this->main_window->main_data_from_file->signals_channels.back().name_of_channel.c_str());
    a->setMinimumHeight(65);
    this->main_window->navigation_window->widget()->layout()->addWidget(a);
    this->close();
}

