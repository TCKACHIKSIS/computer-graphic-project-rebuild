#ifndef TIMESCALEDRAW_H
#define TIMESCALEDRAW_H
#include <QTime>
#include <qwt_scale_draw.h>
#include <qwt_text.h>
#include <iostream>

class TimeScaleDraw: public QwtScaleDraw
{
public:
    TimeScaleDraw();
    virtual QwtText label(double v) const
    {
       int hours = v / 3600;
       v = v - hours*3600;
       int minutes = v / 60;
       v = v - minutes * 60;
       int seconds = v;
       return QString((std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds)).c_str());
    }
private:
    QTime baseTime;
};


#endif // TIMESCALEDRAW_H
