#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H
#include <QPixmap>
#include <QDialog>
#include <QBoxLayout>
#include <QScrollArea>
#include <QButtonGroup>
#include <mainwindow/Widgets/checkboxforchannels.h>
#include <QPushButton>

class MainWindow;

class Spectrogram : public QDialog
{
public:
    Spectrogram();
    Spectrogram( MainWindow *m_wind );

    MainWindow *main_window;
    QBoxLayout *box_layout;
    QScrollArea *scroll_area;
    QBoxLayout *scroll_layout;
    QWidget *scroll_widget;
    QButtonGroup *button_group;
    std::vector<CheckBoxForChannels*> list_of_checkbox;
    QPushButton *action_button;

    void createSpectrogram();

};

#endif // SPECTROGRAM_H
