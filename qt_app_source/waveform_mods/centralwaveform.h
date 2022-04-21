#ifndef CENTRALWAVEFORM_H
#define CENTRALWAVEFORM_H
#include <basewaveform/basewaveform.h>
class MainWindow;

class CentralWaveform : public BaseWaveForm
{
public:
    MainWindow *mainWindow;
    CentralWaveform(CanalOfSignal base, double period_of_tick);
    void mousePressEvent(QMouseEvent *event);
};

#endif // CENTRALWAVEFORM_H
