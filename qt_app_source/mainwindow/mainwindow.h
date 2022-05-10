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
    dataStructure *main_data_from_file;
    std::vector<dataStructure> simulated_signals;
    CentralGridArea *central_grid;
    QTabWidget *main_tab_widget;
    QScrollArea *createWaveformView();
    QScrollArea *main_waveform_area;
    QScrollArea *createWaveformView2(QWidget *parent);
    QMdiArea *right_mdi;
    NavigationWindow *navigation_window;
    DialogWindowFragment *fragment_window;

};
#endif // MAINWINDOW_H
