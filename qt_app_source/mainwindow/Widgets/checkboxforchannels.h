#ifndef CHECKBOXFORCHANNELS_H
#define CHECKBOXFORCHANNELS_H
#include <QCheckBox>
#include <canalofsignal/canalofsignal.h>

class CheckBoxForChannels : public QCheckBox{
public:
    CheckBoxForChannels(const QString &text, CanalOfSignal canal_of_signal, QWidget *parent = nullptr);
    CanalOfSignal canal;
};

#endif // CHECKBOXFORCHANNELS_H
