#ifndef STATISTICS_H
#define STATISTICS_H
#include <QDialog>
#include <canalofsignal/canalofsignal.h>
#include <mainwindow/Widgets/checkboxforchannels.h>
#include <QBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QButtonGroup>
#include <qwt_plot_histogram.h>
#include <QLineEdit>

class MainWindow;

class Statistics : public QDialog
{
public:

    QBoxLayout *box_layout;
    QScrollArea *scroll_area;
    QWidget *scroll_widget;
    QBoxLayout *scroll_layout;

    Statistics( MainWindow *m_wind );
    MainWindow *main_window;
    CanalOfSignal chosen_source_channel;

    std::vector<CheckBoxForChannels*> list_of_checkbox;
    QLineEdit *k_input;

    double average_x;
    double dispersion;
    double standard_deviation;
    double coefficient_of_variation;
    double asymmetry_coefficient;
    double kurtosis_coefficient;
    double max_value;
    double min_value;
    int k_value;

    QwtPlotHistogram *hystogram;
    QwtPlot *plot_for_hystogram;
    QVector<QwtIntervalSample> *intervals_for_histogramm;

    QPushButton *action_button;
    QButtonGroup *button_group;

private:
    void setUi();
    void prepareUiToShowStatistic();
    void showStatistickOfChosenChannel();

    void getAverageX();
    void getDispersion();
    void getStandartDeviation();
    void getCoefficientOfVariation();
    void getAssimetrtCoefficient();
    void getKurtosisCoefficient();
    void getMaxValue();
    void getMinValue();
    void createHistogramm();

};

#endif // STATISTICS_H
