#include "checkboxforchannels.h"

CheckBoxForChannels::CheckBoxForChannels(const QString &text, CanalOfSignal canal_of_signal, QWidget *parent) : QCheckBox(text, parent){
    this->canal = canal_of_signal;
    return;
}
