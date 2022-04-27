#include "dialogwindowfragment.h"
#include <mainwindow/mainwindow.h>

void DialogWindowFragment::fragmentWasChosen(){

    if ( this->start_value->text().isEmpty() || this->end_value->text().isEmpty() ){
        this->close();
        return;
    }
    this->main_window->scaleToChosenFragment(this->start_value->text().toInt(),
                                             this->end_value->text().toInt());
    this->close();
}


DialogWindowFragment::DialogWindowFragment( MainWindow *window )
{
    this->main_window = window;

    QLabel *label = new QLabel();
    label->setText("Введите начальный и конечный отсчет для выделения фрагмента");
    QLabel *start_value_label = new QLabel("Начальный отсчет");
    QLabel *end_value_label = new QLabel("Конечный отсчет");

    this->start_value = new QLineEdit();
    this->end_value = new QLineEdit();

    this->button = new QPushButton();
    button->setText("OK");

    this->grid_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    this->grid_layout->setContentsMargins(20, 20, 20, 20);
    this->grid_layout->addWidget(label);

    this->grid_layout->addWidget(start_value_label);
    this->grid_layout->addWidget(this->start_value);

    this->grid_layout->addWidget(end_value_label);
    this->grid_layout->addWidget(this->end_value);

    this->grid_layout->addWidget(button);

    this->setLayout(grid_layout);

    connect(this->button, &QPushButton::released, this, &DialogWindowFragment::fragmentWasChosen);
}
