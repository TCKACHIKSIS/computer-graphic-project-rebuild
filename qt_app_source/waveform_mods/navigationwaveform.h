#ifndef NAVIGATIONWAVEFORM_H
#define NAVIGATIONWAVEFORM_H
#include <basewaveform/basewaveform.h>
#include <QMainWindow>
class navigationWaveform  : public BaseWaveForm
{
public:
    navigationWaveform(QMainWindow *papasha);
    void add_wave_form_was_clicked();
    QMainWindow *mainWindow;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
signals:
    void add_waveform_to_central_area(const navigationWaveform  *package);
};

#endif // NAVIGATIONWAVEFORM_H
