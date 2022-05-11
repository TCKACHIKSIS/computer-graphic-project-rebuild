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
    dataStructure *main_data_from_file = nullptr;
    std::vector<dataStructure> simulated_signals;
    std::map<std::string, int> counting_simulated_signals = {
        {"DelayedSinglePulse", 0}
    };

    NavigationWindow *navigation_window;
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

private:
    Ui::MainWindow *ui;
    CentralGridArea *central_grid;
    QTabWidget *main_tab_widget;
    QScrollArea *createWaveformView();
    QScrollArea *main_waveform_area;
    QScrollArea *createWaveformView2(QWidget *parent);
    QMdiArea *right_mdi;

    DialogWindowFragment *fragment_window;

};
#endif // MAINWINDOW_H
