#include <GL/glu.h>
#include "pongwidget.h"

PongWidget::PongWidget()
{
}

void PongWidget::initializeGL()
{

    // Enable Smooth Shading
    glShadeModel( GL_SMOOTH);
    // Black Background
    glClearColor(0.0F, 0.0F, 0.0F, 0.5F);
    // Depth Buffer Setup
    glClearDepth(1.0F);
    // Enables Depth Testing
    glEnable( GL_DEPTH_TEST);
    // The Type Of Depth Testing To Do
    glDepthFunc( GL_LEQUAL);
    // Really Nice Perspective Calculations
    glHint( GL_PERSPECTIVE_CORRECTION_HINT,  GL_NICEST);


    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();
    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0F, (width() / (float)height()), 0.1F, 10000.0f);
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.5f, 0, -6);


    glEnable( GL_CULL_FACE); // Enable Culling
    glCullFace( GL_BACK);

    glBlendFunc( GL_SRC_ALPHA,  GL_ONE);
    glEnable( GL_BLEND);

    glEnableClientState( GL_VERTEX_ARRAY);
    glEnableClientState( GL_COLOR_ARRAY);


    // Put in the lights

    float lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1 };
    float lightDiffuse[] = { 1, 1, 1, 1 };
    float lightPosition[] = { 0, 0, 2, 1 };
    float specular[] = { 1, 1, 1, 1 };

    glLightfv( GL_LIGHT1,  GL_AMBIENT, lightAmbient);
    glLightfv( GL_LIGHT1,  GL_DIFFUSE, lightDiffuse);
    glLightfv( GL_LIGHT1,  GL_POSITION, lightPosition);
    glLightfv( GL_LIGHT1,  GL_SPECULAR, specular);
    // Move Left 1.5 Units And Into The Screen 6.0							// Done Drawing The Quad
}

void PongWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();							// Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
    glLoadIdentity();
}

void PongWidget::paintGL()
{
    // Clear Screen And Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    // Top Right
    glTexCoord2f(1, 1);
    glVertex3f(7.6f, 4.58f, -5);
    // Top Left
    glTexCoord2f(0, 1);
    glVertex3f(-4.6f, 4.58f, -5);
    // Bottom Left
    glTexCoord2f(0, 0);
    glVertex3f(-4.6f, -4.57f, -5);
    // Bottom Right
    glTexCoord2f(1, 0);
    glVertex3f(7.6f, -4.57f, -5);
    // Done Drawing The Quad
    glEnd();

}
