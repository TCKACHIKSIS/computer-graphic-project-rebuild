#ifndef SPECTRALANALYSIS_H
#define SPECTRALANALYSIS_H
#include <QDialog>
#include <QButtonGroup>
#include <mainwindow/Widgets/checkboxforchannels.h>
#include <QBoxLayout>
#include <QScrollArea>
#include <QToolBar>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QLineEdit>

class MainWindow;

class SpectralAnalysis : public QDialog
{
public:

    QBoxLayout *box_layout;
    QScrollArea *scroll_area;
    QWidget *scroll_widget;
    QBoxLayout *scroll_layout;
    QPushButton *action_button;
    QButtonGroup *button_group;
    std::vector<CheckBoxForChannels*> list_of_checkbox;
    QToolBar *tool_bar;
    QAction *show_amplitude_spectrum;
    QAction *show_spm;
    QLineEdit *input_L;
    QPushButton *set_L;

    MainWindow *main_window;
    CanalOfSignal chosen_source_channel;

    std::vector<double> dpf_values;

    std::vector<double> amplitude_spectrum;
    QwtPlotCurve *amplitude_specturm_curve;

    std::vector<double> spm;
    QwtPlotCurve *spm_curve;

    int L = 0;

    QwtPlot *plot;

    SpectralAnalysis( MainWindow *m_wind );

    void DoSpectralAnalis();
    void calculateDPF();
    void calculateAmplitudeSpectrum();
    void calculateSPM();
    void paintAmplitudeSpectrum();
    void paintSPM();

    void smooth();

    void setUi();
    void prepareUiToShowStatistic();
};

#endif // SPECTRALANALYSIS_H
