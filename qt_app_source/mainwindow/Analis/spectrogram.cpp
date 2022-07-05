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

    int Ns = this->width_of_image->text().toInt();
    int K = this->height_of_image->text().toInt();

    for ( auto check_button: this->list_of_checkbox ){
        if ( check_button->checkState() ){
            this->chosen_source_channel = check_button->canal;
        }
    }

    for ( auto button: this->list_of_checkbox ){
        delete button;
    }

    delete this->action_button;

    this->calculateSpectrogrammMatrix();
}

void Spectrogram::calculateSpectrogrammMatrix(){
    int Ns = this->width_of_image->text().toInt();
    int K = this->height_of_image->text().toInt();
    delete this->width_of_image;
    delete this->height_of_image;
    double Section_Base = this->chosen_source_channel.number_of_samples / Ns;

    double coeff_n = 1.5;
    int Section_N = (int) (Section_Base * coeff_n);

    int NN;
    int L;
    if (Section_N <= 2 * K)
       {
         NN = 2 * K;
          L = 1;
       }
     else
       {
        L = Section_N / (2 * K);
        if (Section_N % (2 * K) != 0)
        {
          L += 1;
        }

        NN = L * 2 * K;
        }

        double *A = new double[Ns * K];
        double *x = new double[NN];

        for (int ns = 0; ns < Ns; ns++)
         {
          int n0 = (int) (ns * Section_Base);
          for (int i = 0; i < Section_N; i++)
          {
            try
                {
                x[i] = this->chosen_source_channel.values_of_signal[n0 + i];
                 }
                 catch(std::exception)
                 {
                 }
         }

         /* double s = 0;
         for (int i = 0; i < Section_N; i++)
              {
               s += x[i];
         }

         s *= (double) 1 / Section_N;
         for (int i = 0; i < Section_N; i++)
            {
             x[i] -= s;
         }

         for (int i = 0; i < Section_N; i++)
         {
             double w = 0.54 - 0.46 * cos((2 * M_PI * i) / (Section_N - 1));
             x[i] *= w;
         }
         */

         for (int i = Section_N; i < NN; i++)
         {
             std::cout << i << std::endl;
             x[i] = 0;
         }

         if ( L == 1 ){
            std::vector<std::complex<double>> start_values;
            for ( int i = 0; i < NN; i++ ){
                std::complex<double> ptr(x[i], 0);
                start_values.push_back(ptr);
                this->dpf_values.push_back(ptr);
             }


            for ( int i = 0; i < K; i++ ){

               this->amplitude_spectrum_values.push_back( (1.0 / K) *
                       abs(sqrt(pow(this->dpf_values[i].real(), 2) + pow(this->dpf_values[i].imag(), 2)))
                                                          );
            }

            this->spectrogramm_values.push_back(new double[K]);
            for ( int i = 0; i < K; i++ ){
                this->spectrogramm_values.back()[i] = this->amplitude_spectrum_values[i];
            }
         }

    }

       double Amax = this->spectrogramm_values[0][0];

       for ( auto value: this->spectrogramm_values ){
           for ( int i = 0; i < K; i++ ){
               if ( value[i] > Amax ){
                        Amax = value[i];
               }
            }
       }

       for ( int i = 0; i < 256; i++ ){
            this->gray_pallete.push_back(new(int[3]));
            this->gray_pallete.back()[0] = i;
            this->gray_pallete.back()[1] = i;
            this->gray_pallete.back()[2] = i;
            }


       this->spectrogram = new QImage(Ns, K, QImage::Format_RGB32);
       for ( int i = 0; i < K; i++ ){
           for (int j = 0; j < Ns; j++){
               int current_blind = (int)this->spectrogramm_values[i][j]/Amax*1*256;
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
