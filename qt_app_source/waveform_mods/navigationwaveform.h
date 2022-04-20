#ifndef NAVIGATIONWAVEFORM_H
#define NAVIGATIONWAVEFORM_H
#include <basewaveform/basewaveform.h>
#include <QMainWindow>
class MainWindow;

class navigationWaveform  : public BaseWaveForm
{
public:
    navigationWaveform(CanalOfSignal base, double period_of_tick, MainWindow *mwind);
    void add_wave_form_was_clicked();
    MainWindow *mainWindow;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
signals:
    void add_waveform_to_central_area(const navigationWaveform  *package);
};
#endif // NAVIGATIONWAVEFORM_H
