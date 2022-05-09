#ifndef CENTRALWAVEFORM_H
#define CENTRALWAVEFORM_H
#include <basewaveform/basewaveform.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <QPen>
#include <qwt_plot_zoomer.h>
#include <qwt_symbol.h>
class MainWindow;

class CentralWaveform : public BaseWaveForm
{
public:
    MainWindow *mainWindow;
    QwtPlotMagnifier *magnifier;
    QwtPlotPanner *panner;
    QwtPlotPicker *picker = nullptr;
    QwtPlotZoomer *zoomer;
    QwtSymbol *markers = nullptr;

    CentralWaveform(CanalOfSignal base, const dataStructure &data_from_file);
    void mousePressEvent(QMouseEvent *event);
    void changeMarkersVision();
    void changePickerBehavior();
    void enableAxisesFromContext();
    void setAxisBorders();
    void setLocalScale();
    void setGlobalScale();
};

#endif // CENTRALWAVEFORM_H
