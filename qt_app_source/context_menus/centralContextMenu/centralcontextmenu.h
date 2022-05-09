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
    QAction *set_curve_markers;
    QAction *local_scale;
    QAction *global_scale;
    QAction *set_scale;
    QAction *single_global_scale;
    QAction *single_local_scale;
    centralContextMenu(CentralWaveform *parent_plot);
public slots:
    void deleteWaveformFromeCentral();
    void setPickerBehavior();
    void enableAxises();
    void setMarkers();
    void setLocalScale();
    void setGlobalScale();
};

#endif // CENTRALCONTEXTMENU_H
