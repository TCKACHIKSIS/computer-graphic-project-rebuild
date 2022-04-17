#include "navigationcontextmenu.h"
#include <iostream>

NavigationContextMenu::NavigationContextMenu()
{
    this->addAction(new QAction("Action 1", this));
    this->addAction(new QAction("Action 4", this));
    this->addAction(new QAction("Action 3", this));
}
