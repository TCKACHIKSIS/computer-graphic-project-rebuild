#include "spectrogram.h"
#include <mainwindow/mainwindow.h>

Spectrogram::Spectrogram(MainWindow *m_wind)
{
    this->main_window = m_wind;
    this->setStyleSheet("background: white; color: black");


    this->box_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    this->scroll_area = new QScrollArea();
    this->scroll_widget = new QWidget();
    this->scroll_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);

    this->setLayout(this->box_layout);

    this->scroll_widget->setLayout(this->scroll_layout);

    this->scroll_area->setWidget(this->scroll_widget);

    this->box_layout->addWidget(this->scroll_area);

    this->scroll_area->setWidgetResizable(true);

    this->button_group = new QButtonGroup();
    this->button_group->setExclusive(true);

    for ( CanalOfSignal channel: this->main_window->main_data_from_file->signals_channels ){
        CheckBoxForChannels *ptr = new CheckBoxForChannels(channel.name_of_channel.c_str(), channel, this->scroll_widget);
        this->scroll_layout->addWidget(ptr);
        this->button_group->addButton(ptr);
        this->list_of_checkbox.push_back(ptr);
    }

    this->width_of_image = new QLineEdit();
    this->height_of_image = new QLineEdit();

    this->scroll_layout->addWidget(this->width_of_image);
    this->scroll_layout->addWidget(this->height_of_image);

    this->action_button = new QPushButton("OK");
    this->scroll_layout->addWidget(this->action_button);

    connect(this->action_button, &QPushButton::released, this, &Spectrogram::createSpectrogram);

    this->repaint();

}

void Spectrogram::createSpectrogram(){
    for ( auto button: this->list_of_checkbox ){
        delete button;
    }
    this->spectrogram = new QImage(400, 400, QImage::Format_RGB32);

    for ( int i = 1; i <= 400; i++ ){
        for ( int j = 1; j <= 400; j++ ){
            QRgb value;
            value = qRgb(189, 149, 39); // 0xffbd9527
            this->spectrogram->setPixel(i, j, value);
        }
    }

    QLabel *label = new QLabel();
    label->setPixmap(QPixmap::fromImage(*this->spectrogram));
    this->scroll_layout->addWidget(label);
}
