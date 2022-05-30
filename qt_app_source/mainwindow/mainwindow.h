#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMdiArea>
#include <QMainWindow>
#include "filehandler/dataStructure.h"
#include <QTabWidget>
#include <QScrollArea>
#include <mainwindow/centralgridarea.h>
#include <mainwindow/navigationWindow/navigationwindow.h>
#include <waveform_mods/navigationwaveform.h>
#include <mainwindow/dialowWindowFragmet/dialogwindowfragment.h>
#include <utility>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::pair<int, int> *current_scale_central_waveform;

    //прикол
    std::map<int, int> counters_for_simulated_signals = {
        {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0},
        {7, 0}, {8, 0}, {9, 0}, {10, 0}
    };


    dataStructure *main_data_from_file = nullptr;
    dataStructure *simulated_signals = nullptr;
    QMdiArea *right_mdi = nullptr;
    NavigationWindow *navigation_window = nullptr;

    Ui::MainWindow *ui;
    CentralGridArea *central_grid = nullptr;
    QTabWidget *main_tab_widget = nullptr;
    QScrollArea *createWaveformView();
    QScrollArea *main_waveform_area = nullptr;
    QScrollArea *createWaveformView2(QWidget *parent);

    void resetTheCounters();
    void initialInterfaceSetup();
    void clearMainData();
public slots:
    void addWaveformToCentral(const navigationWaveform &package);
    void scaleToChosenFragment(int start, int end);
    void setSingleLocalScale();
    void setSingleGlobalScale();
private slots:
    void on_fileOpen_triggered();

    void on_signalInformation_triggered();

    void on_fragment_triggered();

    void on_resetScale_triggered();


    void on_delayed_single_pulse_triggered();

    void on_delayed_single_jump_triggered();

    void on_discretized_decreasing_exponent_triggered();

    void on_save_file_triggered();

    void on_sample_sine_wave_triggered();

    void on_meandr_triggered();

    void on_saw_triggered();

    void on_exponential_envelope_signal_2_triggered();

    void on_balanced_envelope_signal_triggered();

    void on_signal_with_tonal_envelope_triggered();

    void on_lchs_triggered();

    void on_white_noise_interval_triggered();

    void on_white_noise_with_normal_law_triggered();

    void on_autoregresy_signal_triggered();

private:


    DialogWindowFragment *fragment_window;

};
#endif // MAINWINDOW_H
