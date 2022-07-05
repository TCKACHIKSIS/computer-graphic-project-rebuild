#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H
#include <QPixmap>
#include <QDialog>
#include <QBoxLayout>
#include <QScrollArea>
#include <QButtonGroup>
#include <mainwindow/Widgets/checkboxforchannels.h>
#include <QPushButton>
#include <QImage>
#include <QLineEdit>
#include <canalofsignal/canalofsignal.h>
#include <complex>
#include <QLabel>

class MainWindow;

class Spectrogram : public QDialog
{
public:
    Spectrogram();
    Spectrogram( MainWindow *m_wind );

    MainWindow *main_window;
    QBoxLayout *box_layout;
    QScrollArea *scroll_area;
    QBoxLayout *scroll_layout;
    QWidget *scroll_widget;
    QButtonGroup *button_group;
    std::vector<CheckBoxForChannels*> list_of_checkbox;
    QPushButton *action_button;
    QLineEdit *width_of_image;
    QLineEdit *height_of_image;

    QWidget *tool_widget;
    QBoxLayout *tool_layout;

    CanalOfSignal chosen_source_channel;
    QLineEdit *Coeff;
    QPushButton *set_Coeff;

    std::vector<int*> gray_pallete;
    std::vector<double*> spectrogramm_values;
    std::vector<std::complex<double>> dpf_values;
    std::vector<double> amplitude_spectrum_values;

    void calculateSpectrogrammMatrix();

    QImage *spectrogram;
    void createSpectrogram();
    void repainSpectrogram();
    void setCoeff();

    int current_Coeff = 1;
    double Amax;
    int Ns;
    int K;

    QLabel *image_spectrogram_label = nullptr;

    void resizeEvent(QResizeEvent *event);
};

#endif // SPECTROGRAM_H
