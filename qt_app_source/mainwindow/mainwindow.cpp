#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "filehandler/filehandler.h"
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include <basewaveform/basewaveform.h>
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


void MainWindow::on_fileOpen_triggered()
{
    QString path_to_open_file = QFileDialog::getOpenFileName(this, "Выберите файл", "/", "*.txt");

    if (path_to_open_file.isEmpty() && path_to_open_file.isNull()){
          return;
    }

    FileHandler file;
    file.openFile(path_to_open_file.toStdString());
    if ( !file.isFileOpen()){
       QMessageBox::warning(this, "Внимание", "Ошибка открытия файла");
       return;
     }
    this->main_data_from_file = file.getData();

    this->main_tab_widget = new QTabWidget(this);
    setCentralWidget(main_tab_widget);
    main_tab_widget->show();

    //вынести в отдельный метод
    QScrollArea *scroll = new QScrollArea();
    scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    QWidget* ScrollAreaWidgetContents = new QWidget();
    scroll->setWidget(ScrollAreaWidgetContents);
    QSize AdjustSize = ScrollAreaWidgetContents->size();
    ScrollAreaWidgetContents->setMinimumSize(AdjustSize);

    scroll->setWidgetResizable( true );

    QGridLayout *layout_for_graphic = new QGridLayout(ScrollAreaWidgetContents);

    for ( auto channel: this->main_data_from_file.signals_channels ){
        BaseWaveForm *a = new BaseWaveForm();
        a->createCoordinates(channel, this->main_data_from_file.period_of_tick);
        a->plot = new QwtPlot(this);
        a->createSimplePlot();
        layout_for_graphic->addWidget(a->plot);
    }

    main_tab_widget->addTab(scroll, "Осциллограммы");




    QWidget *info_widget = new QWidget();
    QBoxLayout *box = new QBoxLayout(QBoxLayout::TopToBottom);
    QLabel *label = new QLabel();

    std::string info_string ="Общее число каналов   -   " ;
    label->setText(info_string.c_str());
    box->addWidget(label);

    label = new QLabel();
    info_string = "Общее количество отсчетов    -    " + std::to_string(this->main_data_from_file.number_of_samples);
    label->setText(info_string.c_str());
    box->addWidget(label);

    label = new QLabel();
    info_string = "Частота дискретизации     -    " + std::to_string(this->main_data_from_file.sampling_frequency);
    label->setText(info_string.c_str());
    box->addWidget(label);

    label = new QLabel();
    info_string = "Дата и время начала записи     -    " +this->main_data_from_file.signal_start_date+ this->main_data_from_file.signal_start_time;
    label->setText(info_string.c_str());
    box->addWidget(label);

    label = new QLabel();
    info_string = "Продолжительность записи:     -    " +std::to_string(this->main_data_from_file.recording_duration);
    label->setText(info_string.c_str());
    box->addWidget(label);


    info_widget->setLayout(box);
    main_tab_widget->addTab(info_widget, "Информация о каналах");
}

