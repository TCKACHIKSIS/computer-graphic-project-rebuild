#ifndef BASEPLOTCUSTROMCONTEXTMENU_H
#define BASEPLOTCUSTROMCONTEXTMENU_H
#include<QMenu>
#include<QAction>
class BasePlotCustromContextMenu : public QMenu
{
public:
    BasePlotCustromContextMenu();
    QAction *waveForm;
};

#endif // BASEPLOTCUSTROMCONTEXTMENU_H
