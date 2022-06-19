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
        CheckBoxForChannels *ptr = new CheckBoxForChannels(channel.name_of_channel.c_str(), channel, this->scroll_widget);
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

    connect( this->show_amplitude_spectrum, &QAction::triggered, this, &SpectralAnalysis::paintAmplitudeSpectrum );
    connect( this->show_spm, &QAction::triggered, this, &SpectralAnalysis::paintSPM );

    this->prepareUiToShowStatistic();
    this->calculateDPF();
    this->calculateAmplitudeSpectrum();
    this->calculateSPM();

    this->paintAmplitudeSpectrum();
}

void SpectralAnalysis::calculateAmplitudeSpectrum(){

    this->amplitude_spectrum.clear();

    for ( int i = 0; i <= this->chosen_source_channel.number_of_samples; i++ ){
        this->amplitude_spectrum.push_back(abs(this->dpf_values[i]) * this->chosen_source_channel.sampling_frequency);
    }
}

void SpectralAnalysis::paintAmplitudeSpectrum(){

    this->amplitude_specturm_curve = new QwtPlotCurve();
    this->amplitude_specturm_curve->setPen(Qt::blue, 2);
    QPolygonF points;

    for ( int i = 0; i < this->chosen_source_channel.number_of_samples; i++ ){
        points << QPointF(i, this->amplitude_spectrum[i]);
    }

    this->amplitude_specturm_curve->setSamples(points);

    this->plot->detachItems(QwtPlotItem::Rtti_PlotItem,true);
    this->amplitude_specturm_curve->attach( this->plot );
    this->plot->replot();
}

void SpectralAnalysis::calculateSPM(){
    this->spm.clear();
    for ( int i = 0;  i <= this->chosen_source_channel.number_of_samples; i++ ){
        this->spm.push_back(
                    pow( abs(this->dpf_values[i]), 2 ) * pow( this->chosen_source_channel.sampling_frequency, 2 )
                    );
    }
}

void SpectralAnalysis::paintSPM(){

    this->spm_curve = new QwtPlotCurve();
    this->spm_curve->setPen(Qt::blue, 2);
    QPolygonF points;

    for ( int i = 0; i < this->chosen_source_channel.number_of_samples; i++ ){
        points << QPointF(i, this->spm[i]);
    }

    this->spm_curve->setSamples(points);

    this->plot->detachItems(QwtPlotItem::Rtti_PlotItem,true);
    this->spm_curve->attach(this->plot);
    this->plot->replot();
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
    this->plot = new QwtPlot();

    this->plot->setAxisScaleDraw(QwtPlot::xBottom, new TimeScaleDraw);

    this->scroll_layout->addWidget(this->plot);

    this->input_L = new QLineEdit();
    this->scroll_layout->addWidget(this->input_L);

    this->set_L = new QPushButton("Ввести L");
    this->scroll_layout->addWidget(this->set_L);

    connect(this->set_L, &QPushButton::released, this, &SpectralAnalysis::smooth);

    delete this->button_group;
    delete this->action_button;
}

void SpectralAnalysis::smooth(){
    this->L = this->input_L->text().toUInt();
    if ( this->L == 0 ){
        this->calculateAmplitudeSpectrum();
        this->calculateSPM();
        this->paintAmplitudeSpectrum();
    }
    else {
        int k = 0 ;

        for ( double &value: this->amplitude_spectrum ){
            double ptr = 0;
            for (int l = -1 * this->L ; l <= this->L; l++ ){
                if ( l + k < 0 && l + k >= (int)this->amplitude_spectrum.size() ){
                    break;
                }
                ptr = ptr + this->amplitude_spectrum[l+k];
            }
            value = ptr/(2*this->L + 1);
            k++;
        }

        k = 0;
        for ( double &value: this->spm ){
            double ptr = 0;
            for (int l = -1 * this->L ; l <= this->L; l++ ){
                if ( l + k < 0 && l + k >= (int)this->spm.size() ){
                    break;
                }
                ptr = ptr + this->spm[l+k];
            }
            value = ptr/(2*this->L + 1);
            k++;
        }
        this->paintAmplitudeSpectrum();
    }
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
