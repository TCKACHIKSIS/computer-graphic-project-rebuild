#ifndef CENTRALGRIDAREA_H
#define CENTRALGRIDAREA_H
#include <QWidget>
#include <QGridLayout>

class CentralGridArea : public QWidget
{
public:
    CentralGridArea();
    QGridLayout *grid;
};

#endif // CENTRALGRIDAREA_H
