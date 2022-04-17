#ifndef NAVIGATIONCONTEXTMENU_H
#define NAVIGATIONCONTEXTMENU_H
#include <QMenu>
#include <waveform_mods/navigationwaveform.h>
class NavigationContextMenu : public QMenu
{
public:
    NavigationContextMenu(navigationWaveform *parent_plot);
    QAction *add_waveform;
    navigationWaveform *parentPlot;
public slots:
    void addWaveformEmit();
};

#endif // NAVIGATIONCONTEXTMENU_H
