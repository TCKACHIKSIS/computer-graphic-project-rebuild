#ifndef CENTRALCONTEXTMENU_H
#define CENTRALCONTEXTMENU_H
#include <QMenu>
#include <waveform_mods/centralwaveform.h>

class centralContextMenu : public QMenu
{
public:
    CentralWaveform *parentplot;
    QAction *delete_waveform;
    QAction *set_behavior_picker;
    QAction *enable_axis;
    centralContextMenu(CentralWaveform *parent_plot);
public slots:
    void deleteWaveformFromeCentral();
    void setPickerBehavior();
    void enableAxises();
};

#endif // CENTRALCONTEXTMENU_H
