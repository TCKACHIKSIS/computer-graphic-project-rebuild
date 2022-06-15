#include "spectralanalysis.h"
#include <mainwindow/mainwindow.h>
#include <math.h>
#include <basewaveform/timescaledraw.h>
#include <mainwindow/Analis/dft.h>

SpectralAnalysis::SpectralAnalysis( MainWindow *m_wind )
{
    this->main_window = m_wind;
    this->setStyleSheet("background: white; color: black");

    this->setUi();
    this->button_group = new QButtonGroup();
    this->button_group->setExclusive(true);

    for ( CanalOfSignal channel: this->main_window->main_data_from_file->signals_channels ){
        CheckBoxForChannels *ptr = new CheckBoxForChannels(channel.name_of_channel.c_str() ,channel, this->scroll_widget);
        this->scroll_layout->addWidget(ptr);
        this->button_group->addButton(ptr);
        this->list_of_checkbox.push_back(ptr);
    }
    this->action_button = new QPushButton("OK");
    this->scroll_layout->addWidget(this->action_button);

    connect(this->action_button, &QPushButton::released, this, &SpectralAnalysis::DoSpectralAnalis);

}

void SpectralAnalysis::DoSpectralAnalis(){

    this->setGeometry(this->x(), this->y(), this->width() *4, this->height()*3);

    for ( auto check_button: this->list_of_checkbox ){
        if ( check_button->checkState() ){
            this->chosen_source_channel = check_button->canal;
        }
    }

    this->tool_bar = new QToolBar();
    this->scroll_layout->addWidget(this->tool_bar);

    this->show_amplitude_spectrum = new QAction("Амплитудный спектр");
    this->show_spm = new QAction("СПМ");

    this->tool_bar->addAction(this->show_amplitude_spectrum);
    this->tool_bar->addAction(this->show_spm);

    this->prepareUiToShowStatistic();
    this->calculateDPF();
    this->paintResutlts();
    this->scroll_layout->addWidget(this->plot);
}

void SpectralAnalysis::paintResutlts(){
    this->plot = new QwtPlot();

    this->plot->setAxisScaleDraw(QwtPlot::xBottom, new TimeScaleDraw);


    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setPen( Qt::blue, 2 );
    QPolygonF points;

    for ( int i = 0; i < this->chosen_source_channel.number_of_samples; i++ ){
        points << QPointF(i, this->dpf_values[i]);
    }

    curve->setSamples( points );
    curve->attach( this->plot );
    this->plot->repaint();
}

void SpectralAnalysis::calculateDPF(){
    if ( this->chosen_source_channel.values_of_signal.size() % 2 != 0 ){
        this->chosen_source_channel.values_of_signal.push_back(0);
    }
    this->dpf_values = FFTAnalysis(this->chosen_source_channel.values_of_signal, this->chosen_source_channel.number_of_samples,
                                   this->chosen_source_channel.number_of_samples);

}

void SpectralAnalysis::prepareUiToShowStatistic(){
    for ( auto button: this->list_of_checkbox ){
        delete button;
    }
    delete this->button_group;
    delete this->action_button;
}

void SpectralAnalysis::setUi(){

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
