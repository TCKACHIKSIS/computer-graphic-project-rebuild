#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "filehandler/filehandler.h"
#include <QLabel>
#include <QGridLayout>
#include <basewaveform/basewaveform.h>
#include <base_plot/baseplot.h>
#include <QDialog>
#include <QTableWidget>
#include <QStringList>
#include <QBoxLayout>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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

    this->main_tab_widget = new QTabWidget(this);
    setCentralWidget(main_tab_widget);
    main_tab_widget->show();

    this->main_waveform_area = this->createWaveformView();

    for ( auto channel: this->main_data_from_file->signals_channels ){
        BaseWaveForm *a = new BaseWaveForm();
        a->setTitle(channel.name_of_channel.c_str());
        a->createSimplePlot(channel, this->main_data_from_file->period_of_tick);
        a->setMaximumWidth(this->main_waveform_area->width());
        this->main_waveform_area->widget()->layout()->addWidget(a);
    }

    main_tab_widget->addTab(this->main_waveform_area, "Осциллограммы");
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
