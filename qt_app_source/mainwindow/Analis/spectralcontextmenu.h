#ifndef SPECTRALCONTEXTMENU_H
#define SPECTRALCONTEXTMENU_H
#include <QMenu>

class SpectralAnalysis;

class SpectralContextMenu : public QMenu
{
public:
    SpectralContextMenu(SpectralAnalysis *s_a);
    SpectralAnalysis *parent_window;

    QAction *set_behavior_picker;
    void setPickerBehavior();

    QAction *set_markers_vision;
    void setMarkersVision();
};

#endif // SPECTRALCONTEXTMENU_H
