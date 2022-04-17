#ifndef NAVIGATIONWAVEFORM_H
#define NAVIGATIONWAVEFORM_H
#include <basewaveform/basewaveform.h>
#include <mainwindow/mainwindow.h>
class navigationWaveform  : public BaseWaveForm
{
public:
    navigationWaveform(MainWindow *dad);
    void add_wave_form_was_clicked();
    MainWindow *mainWindow;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
signals:
    void add_waveform_to_central_area(const navigationWaveform& package);
};

#endif // NAVIGATIONWAVEFORM_H
