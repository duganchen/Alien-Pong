#ifdef NO
#include <SFML/Window.hpp>
#endif

#include <GL/gl.h>
#include "paddle.h"

const float Paddle::TOP_WALL_HEIGHT = 1;
const float Paddle::BOTTOM_WALL_HEIGHT = -1;
const float Paddle::HEIGHT = 0.3f;
const float Paddle::SPEED = 0.75f;
const float Paddle::ARENA_LEVEL = 3;
const float Paddle::WIDTH = 0.1f;

Paddle::Paddle(float initialLeft, float initialTop)
{
    paddleLeft = initialLeft;
    paddleTop = initialTop;
    velocity = 0;
}

float Paddle::left()
{
    return paddleLeft;
}
float Paddle::right()
{

    return paddleLeft + WIDTH;
}

float Paddle::top()
{

    return paddleTop;
}

float Paddle::bottom()
{
    return paddleTop - HEIGHT;
}

void Paddle::pushUp(float elapsed)
{
    if (top() < TOP_WALL_HEIGHT)
    {
        paddleTop += SPEED * elapsed;
    }
}

void Paddle::pushDown(float elapsed)
{
    if (top() > BOTTOM_WALL_HEIGHT + HEIGHT)
    {
        paddleTop -= SPEED * elapsed;
    }
}

void Paddle::draw()
{
    glBegin( GL_QUADS);
    //top right
    glVertex3f(right(), top(), ARENA_LEVEL);
    //top left
    glVertex3f(left(), top(), ARENA_LEVEL);
    //bottom left
    glVertex3f(left(), bottom(), ARENA_LEVEL);
    //bottom right
    glVertex3f(right(), bottom(), ARENA_LEVEL);
    glEnd();
}

void Paddle::updateFrame(float elapsed)
{
    paddleTop += velocity * elapsed;

    if (top() >= TOP_WALL_HEIGHT)
        velocity = 0;

    if (top() - HEIGHT <= BOTTOM_WALL_HEIGHT)
        velocity = 0;
}
