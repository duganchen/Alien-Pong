#ifndef PONGWIDGET_H
#define PONGWIDGET_H

#include <QGLWidget>

class PongWidget : public QGLWidget
{
public:
    PongWidget();
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);
};

#endif // PONGWIDGET_H
