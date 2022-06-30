#ifndef SPECTRALCHOOSEFRAGMENTWINDOW_H
#define SPECTRALCHOOSEFRAGMENTWINDOW_H
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
class SpectralAnalysis;

class SpectralChooseFragmentWindow : public QDialog
{
public:
    SpectralChooseFragmentWindow(SpectralAnalysis *s_a, std::pair<int, int> &scale);
    SpectralAnalysis *parent;
    QBoxLayout *grid_layout;
    QLineEdit *start_value;
    QLineEdit *end_value;
    QPushButton *button;
public slots:
     void fragmentWasChosen();
};

#endif // SPECTRALCHOOSEFRAGMENTWINDOW_H
