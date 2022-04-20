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
    navigationWaveform *waveform;

    AddWaveformAction(MainWindow *mainwindow, const char *name, navigationWaveform &package);
    void addToCentral();
};

#endif // ADDWAVEFORMACTION_H
