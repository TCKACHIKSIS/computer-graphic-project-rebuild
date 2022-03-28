#include "basewaveform.h"

BaseWaveForm::BaseWaveForm(QWidget *parent) {
}

void BaseWaveForm::paintEvent(QPaintEvent *) {
  QPainter p(this); // Создаём новый объект рисовальщика
  p.setPen(QPen(Qt::red,1,Qt::SolidLine)); // Настройки рисования
  p.drawLine(0,0,width(),height()); // Рисование линии
}
