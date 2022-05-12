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
    dataStructure *simulated_signals = nullptr;
    QMdiArea *right_mdi = nullptr;
    NavigationWindow *navigation_window = nullptr;

    int count_delayed_single_pulse = 0;

    Ui::MainWindow *ui;
    CentralGridArea *central_grid = nullptr;
    QTabWidget *main_tab_widget = nullptr;
    QScrollArea *createWaveformView();
    QScrollArea *main_waveform_area = nullptr;
    QScrollArea *createWaveformView2(QWidget *parent);

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

private:


    DialogWindowFragment *fragment_window;

};
#endif // MAINWINDOW_H
