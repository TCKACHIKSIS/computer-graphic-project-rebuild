#include "spectrogram.h"
#include <mainwindow/mainwindow.h>

template<class Iter_T>
void fft(Iter_T a, Iter_T b, int log2n);

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

    if ( this->height_of_image->text().isEmpty() || this->width_of_image->text().isEmpty()){
        return;
    }

    this->Ns = this->width_of_image->text().toInt();
    this->K = this->height_of_image->text().toInt();

    for ( auto check_button: this->list_of_checkbox ){
        if ( check_button->checkState() ){
            this->chosen_source_channel = check_button->canal;
        }
    }

    for ( auto button: this->list_of_checkbox ){
        delete button;
    }

    delete this->width_of_image;
    delete this->height_of_image;
    delete this->action_button;



    this->section_base = this->chosen_source_channel.number_of_samples / this->Ns ;
    this->section_n = (int)(this->section_base * this->coeff_n);

    if ( this->section_n <= this->K * 2 ){
        this->L = 1;
        this->NN = this->K * 2;
    }

    if ( this->section_n > this->chosen_source_channel.number_of_samples ){
        this->L = this->section_n / ( 2 * this->K );
        if ( this->section_n % (2 * this->K) != 0 ){
            this->L += 1;
        }
        this->NN = this->L * 2 * this->K;
    }

    std::vector<double> a(this->Ns * this->K);

    for ( int ns = 0; ns < this->chosen_source_channel.number_of_samples; ns++ ){
        int n0 = ns * this->section_base;
        int count_on_mas = n0;
        int count_cnt = 0;
        while ( count_on_mas < this->chosen_source_channel.number_of_samples && count_cnt < this->section_n ){
            a[count_cnt] = this->chosen_source_channel.values_of_signal[count_on_mas];

            count_on_mas++;
            count_cnt++;
        }

        double s = 0;
        count_on_mas = 0;
        count_cnt = 0;

        while ( count_on_mas < this->section_n  ){
            s += a[count_on_mas];
            count_on_mas++;
        }

        s = s / (this->section_n);

        count_on_mas = 0;

        while ( count_on_mas < this->section_n ){
            a[count_on_mas] = a[count_on_mas] - s;
            count_on_mas++;
        }

        count_on_mas = 0;

        while ( count_on_mas < this->section_n ){
            a[count_on_mas] = a[count_on_mas] * (
                        0.54 - 0.46*cos((2*M_PI*count_on_mas)/(this->section_n-1))
                        );
            count_on_mas++;
        }

        count_on_mas = section_n;
        while ( count_on_mas < this->NN ){
            a[count_on_mas] = 0;
            count_on_mas++;
        }

        std::vector<std::complex<double>> start_values;
        count_on_mas = 0;
        for ( auto value: a ){
            std::complex<double> ptr(value, 0);
            start_values.push_back(ptr);
            this->dpf_values.push_back(ptr);
        }

        fft(start_values.begin(), dpf_values.begin(), log2(a.size()));
        if ( this->L == 1 ){
            for ( int i = 0; i < this->dpf_values.size(); i++ ){
                this->amplitude_spectrum_values.push_back(
                            abs(this->dpf_values[i])*this->chosen_source_channel.sampling_frequency
                            );
            }
        }
        if ( this->L > 1 ){
            for ( int i = 0; i < this->NN; i++ ){
                std::cout << this->dpf_values[i] << std::endl;
                this->amplitude_spectrum_values.push_back(
                            abs(this->dpf_values[i])*this->chosen_source_channel.sampling_frequency
                            );
            }
        }

        for ( int k = 0; k < this->K; k++ ){
            double ptr_a = 0;
            for ( int i = (-1*(this->L-1))/2; i <= this->L / 2; i++  ){
                ptr_a = ptr_a + this->amplitude_spectrum_values[this->L*k + i];
            }
            ptr_a = ptr_a/this->L;
            this->amplitude_spectrum_values[k] = ptr_a;
        }

        this->spectrogramm_values.push_back(new double[this->K]);
        for ( int i = 0; i < this->K; i++ ){
            this->spectrogramm_values.back()[i] = this->amplitude_spectrum_values[i];
        }
    }

    this->Amax = this->spectrogramm_values[0][0];

    for ( auto value: this->spectrogramm_values ){
        for ( int i = 0; i < this->K; i++ ){
            if ( value[i] > this->Amax ){
                this->Amax = value[i];
            }
        }
    }

    for ( int i = 0; i < 256; i++ ){
        this->gray_pallete.push_back(new(int[3]));
        this->gray_pallete.back()[0] = i;
        this->gray_pallete.back()[1] = i;
        this->gray_pallete.back()[2] = i;
    }


    this->spectrogram = new QImage(this->Ns, this->K, QImage::Format_RGB32);


    for ( int i = 0; i < this->K; i++ ){
        for (int j = 0; j < this->Ns; j++){
            int current_blind = (int)this->spectrogramm_values[i][j]/this->Amax*this->Coeff*256;
            int I = std::min(255, current_blind);
            QRgb value;
            value = qRgb(this->gray_pallete[I][0], this->gray_pallete[I][1], this->gray_pallete[I][2]);
            this->spectrogram->setPixel(j, i, value);
        }
    }

    QLabel *label = new QLabel();
    label->setPixmap(QPixmap::fromImage(*this->spectrogram));
    this->scroll_layout->addWidget(label);
}
