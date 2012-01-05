#include <QtGui>
#include "instructions.h"

Instructions::Instructions()
{
    QVBoxLayout *layout = new QVBoxLayout();
    QTextEdit *text = new QTextEdit();
    text->setReadOnly(true);
    layout->addWidget(text);
    QString str = "To play, enter the number and size of particles ";
    str.append("trailing the ball. Select the ");
    str.append("resolution, then click Play!\n\n");
    str.append("W - Left Paddle Up\n");
    str.append("S - Left Paddle Down\n");
    str.append("Up - Right Paddle Up\n");
    str.append("Down - Right Paddle Down\n");
    str.append("ESC - Quit\n\n");
    str.append("To stop your paddle, press Up when moving up or Down ");
    str.append("when moving down.\n\n");
    str.append("My system works well with 1024x768 resolution, 128 ");
    str.append("particles of size 20.");
    str.append("I recommend slightly smaller particles for lower ");
    str.append("resolutions and slightly ");
    str.append("bigger particles for higher resolutions. ");

    text->setText(str);
    QPushButton *ok = new QPushButton("Okay");
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(close()));
    layout->addWidget(ok);
    setLayout(layout);
    setWindowTitle("Alien Pong Instructions");
}
