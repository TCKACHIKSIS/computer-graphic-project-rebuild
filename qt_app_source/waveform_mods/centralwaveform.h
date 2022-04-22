#ifndef CENTRALWAVEFORM_H
#define CENTRALWAVEFORM_H
#include <basewaveform/basewaveform.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <QPen>
class MainWindow;

class CentralWaveform : public BaseWaveForm
{
public:
    MainWindow *mainWindow;
    QwtPlotMagnifier *magnifier;
    QwtPlotPanner *panner;
    QwtPlotPicker *picker = nullptr;

    CentralWaveform(CanalOfSignal base, double period_of_tick);
    void mousePressEvent(QMouseEvent *event);
    void changePickerBehavior();
    void enableAxisesFromContext();
};

#endif // CENTRALWAVEFORM_H
