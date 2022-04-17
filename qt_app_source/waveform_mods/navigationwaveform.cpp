#include "navigationwaveform.h"
#include <context_menus/navigationContextMenu/navigationcontextmenu.h>
navigationWaveform::navigationWaveform()
{

}
void navigationWaveform::mousePressEvent(QMouseEvent *event){
    NavigationContextMenu *menu=new NavigationContextMenu();
    menu->popup(this->mapToGlobal(event->pos()));
}
