#include "statistics.h"
#include <mainwindow/mainwindow.h>

Statistics::Statistics( MainWindow *m_wind )
{
    this->main_window = m_wind;

    this->setUi();

    for ( CanalOfSignal channel: this->main_window->main_data_from_file->signals_channels ){
        std::cout << channel.name_of_channel << std::endl;
        CheckBoxForChannels *ptr = new CheckBoxForChannels(channel.name_of_channel.c_str() ,channel, this);
        this->scroll_layout->addWidget(ptr);

    }
}

void Statistics::setUi(){
    this->box_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    this->scroll_area = new QScrollArea();
    this->scroll_widget = new QWidget();
    this->scroll_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);

    this->setLayout(this->box_layout);

    this->scroll_widget->setLayout(this->scroll_layout);

    this->scroll_area->setWidget(this->scroll_widget);

    this->box_layout->addWidget(this->scroll_area);

    this->scroll_area->setWidgetResizable(true);

    this->repaint();
}
