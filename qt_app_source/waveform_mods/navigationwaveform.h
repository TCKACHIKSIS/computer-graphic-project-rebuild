#ifndef NAVIGATIONWAVEFORM_H
#define NAVIGATIONWAVEFORM_H
#include <basewaveform/basewaveform.h>
class navigationWaveform  : public BaseWaveForm
{
public:
    navigationWaveform();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // NAVIGATIONWAVEFORM_H
