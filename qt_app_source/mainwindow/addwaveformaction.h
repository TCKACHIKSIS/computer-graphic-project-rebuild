#ifndef ADDWAVEFORMACTION_H
#define ADDWAVEFORMACTION_H
#include <QAction>
#include <waveform_mods/navigationwaveform.h>

class MainWindow;

class AddWaveformAction : public QAction
{
public:
    navigationWaveform *waveform_from_navigate;
    MainWindow *window;
    AddWaveformAction(MainWindow *mainwindow, const char *name, navigationWaveform &package);
    navigationWaveform *waveform;
    void addToCentral();
};

#endif // ADDWAVEFORMACTION_H
