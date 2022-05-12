

#include "mainwindow/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "filehandler/filehandler.h"
#include <QLabel>
#include <QGridLayout>
#include <waveform_mods/centralwaveform.h>
#include <QDialog>
#include <QTableWidget>
#include <QStringList>
#include <QBoxLayout>
#include <QHeaderView>
#include <QWindow>
#include <QBoxLayout>
#include <mainwindow/addwaveformaction.h>
#include <mainwindow/mainwindow.h>
#include <mainwindow/simulationWindow/delayedsinglepulsewindow.h>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowState(Qt::WindowMaximized);
    this->setStyleSheet("background:white");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QScrollArea* MainWindow::createWaveformView(){

    QScrollArea *scroll = new QScrollArea();
    scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

    QWidget* ScrollAreaWidgetContents = new QWidget();

    scroll->setWidget(ScrollAreaWidgetContents);
    scroll->setWidgetResizable( true );

    QGridLayout *layout_for_waveform = new QGridLayout();
    ScrollAreaWidgetContents->setLayout(layout_for_waveform);

    return scroll;
}

void MainWindow::on_fileOpen_triggered()
{
    QString path_to_open_file = QFileDialog::getOpenFileName(this, "Выберите файл", "/", "*.txt");

    if (path_to_open_file.isEmpty() && path_to_open_file.isNull()){
          return;
    }

    FileHandler file;
    file.openFile(path_to_open_file);
    if ( !file.isFileOpen()){
       QMessageBox::warning(this, "Внимание", "Ошибка открытия файла");
       return;
     }

    this->main_data_from_file = file.getData();

    if ( this->right_mdi != nullptr ){
        this->right_mdi->close();
    }

    this->central_grid = new CentralGridArea();
    this->setCentralWidget(this->central_grid);


    this->main_waveform_area = this->createWaveformView();

    this->navigation_window = new NavigationWindow();

    for ( auto channel: this->main_data_from_file->signals_channels ){
        navigationWaveform *a = new navigationWaveform(channel ,this);
        a->setTitle(channel.name_of_channel.c_str());
        a->setMinimumHeight(65);
        navigation_window->widget()->layout()->addWidget(a);

        AddWaveformAction *waveform_add_action = new AddWaveformAction(this, channel.name_of_channel.c_str(), *a);
        this->ui->waveforms->addAction(waveform_add_action);
    }

    this->central_grid->grid->addWidget(this->main_waveform_area, 0, 0);
    this->central_grid->grid->setColumnStretch(0, 14);


    this->right_mdi = new QMdiArea();

    this->central_grid->grid->setColumnStretch(1, 1);
    this->central_grid->grid->addWidget(right_mdi, 0, 1);
    this->right_mdi->setFixedSize(170, 600);
    this->navigation_window->setFixedSize(170, 600);
    this->right_mdi->addSubWindow(navigation_window, Qt::FramelessWindowHint);

    if ( this->current_scale_central_waveform != nullptr ){
        this->current_scale_central_waveform = nullptr;
    }
    this->current_scale_central_waveform = new std::pair<int, int>();
    this->current_scale_central_waveform->first = 0;
    this->current_scale_central_waveform->second = 0;
}


void MainWindow::addWaveformToCentral(const navigationWaveform &package){
    CentralWaveform *a = new CentralWaveform(package.foundation, this);
    a->setTitle(a->foundation.name_of_channel.c_str());
    a->setMaximumWidth(this->main_waveform_area->width());
    a->setMinimumHeight(this->main_waveform_area->height()/5);
    this->main_waveform_area->widget()->layout()->addWidget(a);

}


void MainWindow::on_signalInformation_triggered()
{
   if (this->main_data_from_file == nullptr){
       QMessageBox msg;
       msg.setText("Нет открытого канала");
       msg.exec();
       return;
   }


   std::string information_text ="Общее число каналов: " + std::to_string(this->main_data_from_file->number_of_channels);
   information_text += "\nОбщее количество отсчетов: " + std::to_string(this->main_data_from_file->number_of_samples);
   information_text +="\nЧастота дискретизации: " + std::to_string(this->main_data_from_file->sampling_frequency) + "Гц";
   information_text +="\nДата и время начала записи: " +
                              this->main_data_from_file->signal_start_date + " " +
                              this->main_data_from_file->signal_start_time;
   information_text += "\nДата и время окончания записи: ";
   information_text += "\nДлительность: ";


   QDialog info;
   QBoxLayout layout_for_info(QBoxLayout::TopToBottom);
   info.setLayout(&layout_for_info);

   QLabel label;
   label.setText(information_text.c_str());
   info.layout()->addWidget(&label);

   QTableWidget table;
   table.setColumnCount(3);
   table.setShowGrid(true);
   QStringList headers;
   headers.append("N");
   headers.append("Имя");
   headers.append("Источник");
   table.setHorizontalHeaderLabels(headers);
   table.verticalHeader()->hide();
   int i = 0;
   int number_of_channel = 1;
   for ( auto channel: this->main_data_from_file->signals_channels ){
       table.insertRow(i);
       table.setItem(i, 0 ,new QTableWidgetItem(std::to_string(number_of_channel).c_str()));
       table.setItem(i, 1 ,new QTableWidgetItem(channel.name_of_channel.c_str()));
       table.setItem(i, 2 ,new QTableWidgetItem(channel.source_of_channel.c_str()));
       i++;
       number_of_channel++;
   }

   info.layout()->addWidget(&table);

   info.exec();
   return;
}

void MainWindow::on_fragment_triggered()
{
    if (this->main_data_from_file == nullptr ){
        QMessageBox msg;
        msg.setText("Нет открытого канала");
        msg.exec();
        return;
    }
    this->fragment_window = new DialogWindowFragment(this, *this->current_scale_central_waveform);
    this->fragment_window->exec();
}

void MainWindow::scaleToChosenFragment(int start, int end){
    for ( int i = 0; i < this->main_waveform_area->widget()->layout()->count(); i++ ){
        this->current_scale_central_waveform->first = start;
        this->current_scale_central_waveform->second = end;
        CentralWaveform *widget = (CentralWaveform*)this->main_waveform_area->widget()->layout()->itemAt(i)->widget();
        widget->setAxisScale(QwtPlot::xBottom, this->main_data_from_file->period_of_tick*start, this->main_data_from_file->period_of_tick*end);
        widget->replot();
    }

    return;
}

void MainWindow::on_resetScale_triggered()
{
  this->current_scale_central_waveform->first = 0;
  this->current_scale_central_waveform->second = 0;
  for ( int i = 0; i < this->main_waveform_area->widget()->layout()->count(); i++ ){
        CentralWaveform *widget = (CentralWaveform*)this->main_waveform_area->widget()->layout()->itemAt(i)->widget();
        widget->setAxisAutoScale(QwtPlot::xBottom);
        widget->setAxisAutoScale(QwtPlot::yLeft);
        widget->replot();
    }
}

void MainWindow::setSingleLocalScale(){
    if ( this->main_waveform_area->widget()->layout()->isEmpty() ){
        return;
    }
    //здесь криво сделано, два раза первый элемент проходит и вообще все криво и уеби*но ты червяк, будет время- пределай
    std::pair<double, double> scale_y_borders;
    CentralWaveform *widget = (CentralWaveform*)this->main_waveform_area->widget()->layout()->itemAt(0)->widget();
    scale_y_borders = widget->getMaxAndMinValueOfSignalInFramgent();

    for ( int i = 0; i < this->main_waveform_area->widget()->layout()->count(); i++ ){
        widget = (CentralWaveform*)this->main_waveform_area->widget()->layout()->itemAt(i)->widget();
        std::pair<double, double> ptr = widget->getMaxAndMinValueOfSignalInFramgent();
        if ( ptr.first < scale_y_borders.first ){
            scale_y_borders.first = ptr.first;
        }
        if ( ptr.second > scale_y_borders.second ){
            scale_y_borders.second = ptr.second;
        }
    }
    for ( int i = 0; i < this->main_waveform_area->widget()->layout()->count(); i++ ){
        widget = (CentralWaveform*)this->main_waveform_area->widget()->layout()->itemAt(i)->widget();
        widget->setAxisScale(QwtPlot::yLeft, scale_y_borders.first, scale_y_borders.second );
        widget->replot();
    }
    return;
}

void MainWindow::setSingleGlobalScale(){
    if ( this->main_waveform_area->widget()->layout()->isEmpty() ){
        return;
    }
    //здесь криво сделано, два раза первый элемент проходит и вообще все криво и уеби*но ты червяк, будет время- пределай
    std::pair<double, double> scale_y_borders;
    CentralWaveform *widget = (CentralWaveform*)this->main_waveform_area->widget()->layout()->itemAt(0)->widget();
    scale_y_borders = widget->getMaxAndMinInAllSignal();

    for ( int i = 0; i < this->main_waveform_area->widget()->layout()->count(); i++ ){
        widget = (CentralWaveform*)this->main_waveform_area->widget()->layout()->itemAt(i)->widget();
        std::pair<double, double> ptr = widget->getMaxAndMinInAllSignal();
        if ( ptr.first < scale_y_borders.first ){
            scale_y_borders.first = ptr.first;
        }
        if ( ptr.second > scale_y_borders.second ){
            scale_y_borders.second = ptr.second;
        }
    }
    for ( int i = 0; i < this->main_waveform_area->widget()->layout()->count(); i++ ){
        widget = (CentralWaveform*)this->main_waveform_area->widget()->layout()->itemAt(i)->widget();
        widget->setAxisScale(QwtPlot::yLeft, scale_y_borders.first, scale_y_borders.second );
        widget->replot();
    }
    return;
}




void MainWindow::on_delayed_single_pulse_triggered()
{
    DelayedSinglePulseWindow *d_s_p_window = new DelayedSinglePulseWindow(this);
    d_s_p_window->exec();
}

