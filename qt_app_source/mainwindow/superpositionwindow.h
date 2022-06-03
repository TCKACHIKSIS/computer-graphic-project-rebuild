#ifndef SUPERPOSITIONWINDOW_H
#define SUPERPOSITIONWINDOW_H
#include <QDialog>
#include <QCheckBox>
#include <QBoxLayout>
#include <QPushButton>
#include <vector>
#include <canalofsignal/canalofsignal.h>
#include <QLineEdit>
#include <mainwindow/Widgets/checkboxforchannels.h>

typedef struct CheckBoxForChannelsAndLineEditForCoef{
    CheckBoxForChannels *check_box;
    QLineEdit *line_edit;
}CheckBoxForChannelsAndLineEditForCoef;

class MainWindow;

class SuperPositionWindow : public QDialog
{
public:
    SuperPositionWindow( MainWindow *m_wind);
    MainWindow *main_window;
    QBoxLayout *box_layout;
    QPushButton *create_superposition_button;
    std::vector<CheckBoxForChannelsAndLineEditForCoef*> check_box_list;
    void createSuperposition();
    QCheckBox *multiplication;
    QCheckBox *addition;
};

#endif // SUPERPOSITIONWINDOW_H
