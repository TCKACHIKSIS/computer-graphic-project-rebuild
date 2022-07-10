#ifndef FREQUENCYSCALEDRAW_H
#define FREQUENCYSCALEDRAW_H
#include <qwt_scale_draw.h>
#include <qwt_text.h>
#include <math.h>
#include <canalofsignal/canalofsignal.h>

class FrequencyScaleDraw : public QwtScaleDraw
{
public:
    FrequencyScaleDraw(CanalOfSignal *s);
    CanalOfSignal *source;
    virtual QwtText label(double v) const{
        v = (source->sampling_frequency * v) / source->number_of_samples;
        v = round(v*100)/100;
        return QString((std::to_string(v) + " Гц").c_str());
    }
};

#endif // FREQUENCYSCALEDRAW_H
