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
#include <QCheckBox>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <mainwindow/Analis/spectralcontextmenu.h>
#include <qwt_symbol.h>
#include <mainwindow/Analis/spectralchoosefragmentwindow.h>
#include <complex>

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
    QAction *choose_fragment;
    QAction *set_log_display;
    QAction *set_linear_display;
    QAction *reset_scale;
    QLineEdit *input_L;
    QPushButton *set_L;

    std::pair<int, int> current_scale;
    SpectralChooseFragmentWindow *s_c_f_w;
    void showChooseFragmentWindow();
    void scaleToChosenFragment(int start, int end);
    void resetScale();

    QPushButton *do_nothing;
    QPushButton *become_zero;
    QPushButton *become_module;

    int current_resolve_collision = 0;
    void reCalcDPF();

    MainWindow *main_window;
    CanalOfSignal chosen_source_channel;

    std::vector<std::complex<double>> dpf_values;

    std::vector<double> amplitude_spectrum;
    std::vector<double> log_amplitude_spectrum;

    QwtPlotCurve *amplitude_specturm_curve;

    std::vector<double> spm;
    std::vector<double> log_spm;

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

    bool is_log = false;
    void setLogDisplay();
    void setLinearDisplay();

    void setUi();
    void prepareUiToShowStatistic();

    void mousePressEvent(QMouseEvent *event);

    QwtPlotPicker *picker = nullptr;
    void changePickerBehavior();

    bool is_markers_visible = false;
    QwtSymbol *markers = nullptr;
    void changeMarkersVision();
};

#endif // SPECTRALANALYSIS_H
