#include "centralgridarea.h"

CentralGridArea::CentralGridArea()
{
    this->grid = new QGridLayout();
    this->setLayout(this->grid);
}
