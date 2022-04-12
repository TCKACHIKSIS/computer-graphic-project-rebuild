#include "navigationwindow.h"
#include <QGridLayout>
NavigationWindow::NavigationWindow()
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QWidget* ScrollAreaWidgetContents = new QWidget();

    this->setWidget(ScrollAreaWidgetContents);
    this->setWidgetResizable( true );

    QGridLayout *layout_for_waveform = new QGridLayout();
    ScrollAreaWidgetContents->setLayout(layout_for_waveform);

}
