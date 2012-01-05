#ifndef GUI_H
#define GUI_H

#include <QtGui>
#include "instructions.h"

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = 0);
    ~GUI();
private:
    Instructions *instructions;
    QSpinBox *particleCount;
    QDoubleSpinBox *particleSize;
    QButtonGroup *resolutions;
    QAbstractButton *xga;
    QComboBox *planets;
    unsigned int width(const QString &dimensions) const;
    unsigned int height(const QString &dimensions) const;
private slots:
    void setDefaults();
    void play();
};

#endif // GUI_H
