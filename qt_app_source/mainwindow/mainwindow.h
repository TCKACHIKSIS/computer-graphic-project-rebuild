#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filehandler/dataStructure.h"
#include <QTabWidget>
#include <QScrollArea>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fileOpen_triggered();

private:
    Ui::MainWindow *ui;
    dataStructure main_data_from_file;
    QTabWidget *main_tab_widget;
    QScrollArea *createWaveformView();
    QScrollArea *main_waveform_area;
};
#endif // MAINWINDOW_H
