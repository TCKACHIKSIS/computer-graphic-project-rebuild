#ifndef CENTRALCONTEXTMENU_H
#define CENTRALCONTEXTMENU_H
#include <QMenu>
#include <waveform_mods/centralwaveform.h>

class centralContextMenu : public QMenu
{
public:
    CentralWaveform *parentplot;
    QAction *delete_waveform;
    centralContextMenu(CentralWaveform *parent_plot);
public slots:
    void deleteWaveformFromeCentral();
};

#endif // CENTRALCONTEXTMENU_H
