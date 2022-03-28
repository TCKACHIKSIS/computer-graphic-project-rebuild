#ifndef BASEWAVEFORM_H
#define BASEWAVEFORM_H
#include <QWidget>
#include <QPainter>

class BaseWaveForm : public QWidget
{
public:
    BaseWaveForm(QWidget * parent = 0);
protected:
  void paintEvent(QPaintEvent *);
};

#endif // BASEWAVEFORM_H
