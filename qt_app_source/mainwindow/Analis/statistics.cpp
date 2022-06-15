#include "statistics.h"
#include <mainwindow/mainwindow.h>

typedef struct interval{
    double min_value;
    double max_value;
    int amount;
    interval( double min, double max, double a ){
        this->min_value = min;
        this->max_value = max;
        this->amount = a;
    }
}interval;

Statistics::Statistics( MainWindow *m_wind )
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

    this->k_input = new QLineEdit();
    this->scroll_layout->addWidget(this->k_input);

    this->action_button = new QPushButton("OK");
    this->scroll_layout->addWidget(this->action_button);

    connect(this->action_button, &QPushButton::released, this, &Statistics::showStatistickOfChosenChannel);
}


//значение ты копируешь тут, потому что плохо написал класс чекбоксов, не разобрался там в ошибке
void Statistics::showStatistickOfChosenChannel(){

    if ( this->k_input->text().size() == 0 ){
        return;
    }

    for ( auto check_button: this->list_of_checkbox ){
        if ( check_button->checkState() ){
            this->chosen_source_channel = check_button->canal;
        }
    }

    this->k_value = this->k_input->text().toInt();

    this->prepareUiToShowStatistic();

    QLabel *label = new QLabel("Статистика");
    this->scroll_layout->addWidget(label);

    this->setGeometry(this->x()-300, this->y()-200, this->width()*3, this->height()*4);

    this->getAverageX();

    std::string ptr_for_out = "Среднее: " + std::to_string(this->average_x);
    label = new QLabel(ptr_for_out.c_str());
    this->scroll_layout->addWidget(label);

    this->getDispersion();

    ptr_for_out = "Дисперсия: " + std::to_string(this->dispersion);
    label = new QLabel(ptr_for_out.c_str());
    this->scroll_layout->addWidget(label);

    this->getStandartDeviation();

    ptr_for_out = "Среднеквадратичное отклонение: " + std::to_string(this->standard_deviation);
    label = new QLabel(ptr_for_out.c_str());
    this->scroll_layout->addWidget(label);

    this->getCoefficientOfVariation();

    ptr_for_out = "Коэффициент вариации: " + std::to_string(this->coefficient_of_variation);
    label = new QLabel(ptr_for_out.c_str());
    this->scroll_layout->addWidget(label);

    this->getAssimetrtCoefficient();

    ptr_for_out = "Коэффициент асимметрии: " + std::to_string(this->asymmetry_coefficient);
    label = new QLabel(ptr_for_out.c_str());
    this->scroll_layout->addWidget(label);

    this->getKurtosisCoefficient();

    ptr_for_out = "Коэффициент эксцесса: " + std::to_string(this->kurtosis_coefficient);
    label = new QLabel(ptr_for_out.c_str());
    this->scroll_layout->addWidget(label);

    this->getMaxValue();

    ptr_for_out = "Максимальное значение: " + std::to_string(this->max_value);
    label = new QLabel(ptr_for_out.c_str());
    this->scroll_layout->addWidget(label);

    this->getMinValue();

    ptr_for_out = "Минимальное значение: " + std::to_string(this->min_value);
    label = new QLabel(ptr_for_out.c_str());
    this->scroll_layout->addWidget(label);

    this->createHistogramm();
    label = new QLabel("Распределение значений сигнала");
    this->scroll_layout->addWidget(label);
    this->scroll_layout->addWidget(this->plot_for_hystogram);

}

void Statistics::createHistogramm(){
    this->hystogram = new QwtPlotHistogram();
    this->hystogram->setPen(QPen(QColor(255, 0, 0, 255)));
    this->hystogram->setBrush(QBrush(QColor(0, 255, 0, 255)));

    this->plot_for_hystogram = new QwtPlot();

    this->intervals_for_histogramm = new QVector<QwtIntervalSample>;

    double h = (double)(this->max_value - this->min_value);
    h = h / (double)this->k_value;


    std::vector<interval> intervals;
    double min_interval = this->min_value;
    double max_interval = this->min_value + h;
    while ( (float)this->max_value - (float)max_interval >= 0 ){
        intervals.push_back(interval(min_interval, max_interval, 0));
        min_interval = max_interval;
        max_interval += h;
    }
    if ( (float) this->max_value - (float) max_interval > 0 ){
        intervals.push_back(interval(min_interval, max_interval, 0));
    }

    //очень медленно
    for ( auto value: this->chosen_source_channel.values_of_signal ){
        for ( auto &interv: intervals ){
            std::cout << "Интервал: " << interv.min_value << " " << interv.max_value << ". " << "Значение: " << value << " Условие: " <<std::endl;
            if ( ((float)value - (float)interv.min_value > 0) && ( (float)interv.max_value - (float)value >= 0) ){
                interv.amount++;
                break;
            }
        }
    }

    for ( auto value: this->chosen_source_channel.values_of_signal ){
        if ( value == intervals.front().min_value ){
            intervals.front().amount++;
        }
    }


    for ( auto interv: intervals ){
        this->intervals_for_histogramm->append(QwtIntervalSample(interv.amount,  interv.min_value, interv.max_value ));
    }

    this->hystogram->setSamples(*this->intervals_for_histogramm);
    this->hystogram->attach(this->plot_for_hystogram);

}

void Statistics::getKurtosisCoefficient(){
    this->kurtosis_coefficient = 0;
    for ( auto value: this->chosen_source_channel.values_of_signal ){
        this->kurtosis_coefficient = this->kurtosis_coefficient + pow( (value - this->average_x), 4);
    }
    this->kurtosis_coefficient = this->kurtosis_coefficient / (double)this->chosen_source_channel.number_of_samples;
    this->kurtosis_coefficient = this->kurtosis_coefficient / pow(this->standard_deviation, 4);
    this->kurtosis_coefficient -= 3;
}

void Statistics::getMaxValue(){
     this->max_value = *std::max_element(this->chosen_source_channel.values_of_signal.begin(),
                                            this->chosen_source_channel.values_of_signal.end());
}

void Statistics::getMinValue(){
    this->min_value = *std::min_element(this->chosen_source_channel.values_of_signal.begin(),
                                        this->chosen_source_channel.values_of_signal.end());
}

void Statistics::getAssimetrtCoefficient(){
    this->asymmetry_coefficient = 0;
    for ( auto value: this->chosen_source_channel.values_of_signal ){
        this->asymmetry_coefficient = this->asymmetry_coefficient + pow( (value - this->average_x), 3);
    }
    this->asymmetry_coefficient = this->asymmetry_coefficient / (double)this->chosen_source_channel.number_of_samples;
    this->asymmetry_coefficient = this->asymmetry_coefficient / pow(this->standard_deviation, 3);
}

void Statistics::getCoefficientOfVariation(){
    this->coefficient_of_variation = this->standard_deviation / this->average_x;
}

void Statistics::getAverageX(){
    this->average_x = 0;
    for ( auto value: this->chosen_source_channel.values_of_signal ){
        this->average_x += value;
    }
    this->average_x = this->average_x / (double)this->chosen_source_channel.number_of_samples;
}

void Statistics::getDispersion(){
    this->dispersion = 0;
    for ( auto value: this->chosen_source_channel.values_of_signal ){
        this->dispersion = this->dispersion + pow((value - this->average_x ), 2);
    }
    this->dispersion = this->dispersion /  (double)this->chosen_source_channel.number_of_samples;
}

void Statistics::getStandartDeviation(){
    this->standard_deviation = sqrt(this->dispersion);
}

void Statistics::prepareUiToShowStatistic(){
    for ( auto button: this->list_of_checkbox ){
        delete button;
    }
    delete this->k_input;
    delete this->button_group;
    delete this->action_button;
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
