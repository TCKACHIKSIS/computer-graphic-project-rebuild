#include "spectrogram.h"
#include <mainwindow/mainwindow.h>
#include <QAction>
#include <mainwindow/Analis/dft.h>



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
    this->Ns = this->width_of_image->text().toInt();
    this->K = this->height_of_image->text().toInt();
    delete this->width_of_image;
    delete this->height_of_image;
    double Section_Base = (double)this->chosen_source_channel.number_of_samples / (double)Ns;


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

        double *x = new double[NN];
        this->A = new double[this->Ns*this->K];

        for (int ns = 0; ns < Ns; ns++)
         {
          if ( !this->amplitude_spectrum_values.empty() ){
              this->amplitude_spectrum_values.clear();
          }
          if ( !this->dpf_values.empty() ){
              this->dpf_values.clear();
          }
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

         double s = 0;
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


         for (int i = Section_N; i < NN; i++)
         {
             x[i] = 0;
         }

         if ( L == 1 ){
            std::vector<std::complex<double>> start_values;
            for ( int i = 0; i < NN; i++ ){
                std::complex<double> ptr(x[i], 0);
                start_values.push_back(ptr);
                this->dpf_values.push_back(ptr);
             }


            fft(start_values.begin(), dpf_values.begin(), log2(start_values.size()));

            for ( int i = 0; i < K; i++ ){
               this->amplitude_spectrum_values.push_back( (1.0 / K) *
                       (abs(this->dpf_values[i].real()) + abs(this->dpf_values[i].imag()))*this->chosen_source_channel.sampling_frequency
                                                          );
            }

            this->spectrogramm_values.push_back(new double[K]);
            for ( int i = 0; i < K; i++ ){
                this->spectrogramm_values.back()[i] = this->amplitude_spectrum_values[i] ;
            }
         }
         else {

         }

    }

       this->Amax = this->spectrogramm_values[0][0];

       for ( auto value: this->spectrogramm_values ){
           for ( int i = 0; i < K; i++ ){
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

       for ( int i = 0; i <= 85; i++ ){
           this->copper_pallete.push_back(new(int[3]));
           this->copper_pallete.back()[0] = i;
           this->copper_pallete.back()[1] = i * 8;
           this->copper_pallete.back()[2] = i * 3;
       }
       for ( int i = 86; i <= 170; i++ ){
           this->copper_pallete.push_back(new(int[3]));
           this->copper_pallete.back()[0] = 0;
           this->copper_pallete.back()[1] = i * 8;
           this->copper_pallete.back()[2] = i * 3;
       }
       for ( int i = 171; i < 256; i++ ){
           this->copper_pallete.push_back(new(int[3]));
           this->copper_pallete.back()[0] = 0;
           this->copper_pallete.back()[1] = 170;
           this->copper_pallete.back()[2] = 255;
       }

       for ( int i = 0; i <= 85; i++ ){
           this->hot_pallete.push_back(new(int[3]));
           this->hot_pallete.back()[0] = 0;
           this->hot_pallete.back()[1] = 0;
           this->hot_pallete.back()[2] = i * 3;
       }
       for ( int i = 86; i <= 170; i++ ){
           this->hot_pallete.push_back(new(int[3]));
           this->hot_pallete.back()[0] = 0;
           this->hot_pallete.back()[1] = (i - 85)*3;
           this->hot_pallete.back()[2] = 255;
       }
       for ( int i = 171; i < 256; i++ ){
           this->hot_pallete.push_back(new(int[3]));
           this->hot_pallete.back()[0] = (i - 170) * 3;
           this->hot_pallete.back()[1] = 255;
           this->hot_pallete.back()[2] = 255;
       }

       for ( int i = 0; i <= 85; i++ ){
           this->cool_pallete.push_back(new(int[3]));
           this->cool_pallete.back()[0] = 255;
           this->cool_pallete.back()[1] = i * 3;
           this->cool_pallete.back()[2] = 0;
       }
       for ( int i = 86; i <= 170; i++ ){
           this->cool_pallete.push_back(new(int[3]));
           this->cool_pallete.back()[0] = 0;
           this->cool_pallete.back()[1] = 255;
           this->cool_pallete.back()[2] = (i - 85) * 3;
       }
       for ( int i = 171; i < 256; i++ ){
           this->cool_pallete.push_back(new(int[3]));
           this->cool_pallete.back()[0] = 0;
           this->cool_pallete.back()[1] = 0;
           this->cool_pallete.back()[2] = (i - 170) * 3;
       }

       this->current_pallete = this->gray_pallete;

       this->spectrogram = new QImage(Ns, K, QImage::Format_RGB32);

       for ( int i = 0; i < Ns; i++ ){
           for (int j = 0; j < K; j++){
               int current_blind = this->spectrogramm_values[i][j]/this->Amax*this->current_Coeff*256;
               int I = std::min(255, current_blind);
               QRgb value;
               value = qRgb(this->current_pallete[I][0], this->current_pallete[I][1], this->current_pallete[I][2]);
               this->spectrogram->setPixel(i, j, value);
           }
       }
       this->scroll_layout->setContentsMargins(0, 0, 0, 0);

       this->tool_widget = new QWidget();
       this->tool_layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
       this->tool_widget->setLayout(this->tool_layout);
       this->scroll_layout->addWidget(this->tool_widget);

       this->Coeff = new QLineEdit();
       this->tool_layout->addWidget(this->Coeff);

       this->set_Coeff = new QPushButton("Установить Coeff");
       this->tool_layout->addWidget(this->set_Coeff);
       connect(this->set_Coeff, &QPushButton::released, this, &Spectrogram::setCoeff);

       this->set_gray = new QPushButton("GRAY");
       this->set_copper = new QPushButton("COPPER");
       this->set_hot = new QPushButton("HOT");
       this->set_cool = new QPushButton("COOL");

       connect(this->set_gray, &QPushButton::released, this, &Spectrogram::setGray);
       connect(this->set_copper, &QPushButton::released, this, &Spectrogram::setCopper);
       connect(this->set_hot, &QPushButton::released, this, &Spectrogram::setHot);
       connect(this->set_cool, &QPushButton::released, this, &Spectrogram::setCool);

       this->tool_layout->addWidget(this->set_gray);
       this->tool_layout->addWidget(this->set_copper);
       this->tool_layout->addWidget(this->set_hot);
       this->tool_layout->addWidget(this->set_cool);

       this->image_spectrogram_label = new QLabel();
       this->image_spectrogram_label->setPixmap(QPixmap::fromImage(*this->spectrogram));
       this->image_spectrogram_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
       this->scroll_layout->addWidget(this->image_spectrogram_label);

       this->image_spectrogram_label->setScaledContents(true);

       this->scroll_layout->addStretch(1);

       this->image_spectrogram_label->setFixedWidth(this->width());
       this->image_spectrogram_label->setFixedHeight(this->height());

}

void Spectrogram::setGray(){
    this->current_pallete = this->gray_pallete;
    this->repainSpectrogram();
}

void Spectrogram::setCopper(){
    this->current_pallete = this->copper_pallete;
    this->repainSpectrogram();
}

void Spectrogram::setHot(){
    this->current_pallete = this->hot_pallete;
    this->repainSpectrogram();
}

void Spectrogram::setCool(){
    this->current_pallete = this->cool_pallete;
    this->repainSpectrogram();
}

void Spectrogram::resizeEvent(QResizeEvent *event){
    if ( this->image_spectrogram_label != nullptr ){
        this->image_spectrogram_label->setFixedWidth(this->width() - 70);
        this->image_spectrogram_label->setFixedHeight(this->height() - 70);
    }
}

void Spectrogram::setCoeff(){
    this->current_Coeff = this->Coeff->text().toInt();
    this->repainSpectrogram();
}

void Spectrogram::repainSpectrogram(){
    for ( int i = 0; i < Ns; i++ ){
        for (int j = 0; j < K; j++){
            int current_blind = this->spectrogramm_values[i][j]/this->Amax*this->current_Coeff*256;
            int I = std::min(255, current_blind);
            QRgb value;
            value = qRgb(this->current_pallete[I][0], this->current_pallete[I][1], this->current_pallete[I][2]);
            this->spectrogram->setPixel(i, j, value);
        }
    }
    this->image_spectrogram_label->setPixmap(QPixmap::fromImage(*this->spectrogram));
    this->image_spectrogram_label->repaint();
}

