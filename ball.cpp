#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <GL/gl.h>
#include "ball.h"

Ball::Ball()
{
    moveToCenter();
}

const float Ball::SPEED;

float Ball::top()
{
    return y;
}

float Ball::bottom()
{
    return y - WIDTH;
}

float Ball::left()
{
    return x;
}


float Ball::right()
{
    return x + WIDTH;
}

bool Ball::isLeftBound()
{
    return xVelocity < 0;
}

bool Ball::isRightBound()
{
    return xVelocity > 0;
}

float Ball::speed()
{
    return Ball::SPEED;
}

void Ball::moveToCenter()
{
    x = MIDDLE_X;
    y = 0;

	/*
    xVelocity = sf::Randomizer::Random(0, 1) == 0 ? SPEED : -SPEED;
    yVelocity = sf::Randomizer::Random(0, 1) == 0 ? Ball::SPEED : -Ball::SPEED;
	*/
	xVelocity = SPEED;
	yVelocity = SPEED;
}

void Ball::draw()
{
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    //top right

    glTexCoord2f(1.0, 1.0);

    glVertex3f(right(), top(), ARENA_LEVEL);
    //top left

    glTexCoord2f(0.0, 1.0);
    glVertex3f(left(), top(), ARENA_LEVEL);
    //bottom left

    glTexCoord2f(0.0, 0.0);
    glVertex3f(left(), bottom(), 3);
    //bottom right

    glTexCoord2f(1.0, 0.0);
    glVertex3f(right(), bottom(), ARENA_LEVEL);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Ball::updateFrame(float elapsed)
{
    x += xVelocity * elapsed;
    y += yVelocity * elapsed;
}

void Ball::bounceHorizontally()
{
    x = xVelocity < 0 ? ARENA_LEFT : ARENA_RIGHT - WIDTH;
    xVelocity = -xVelocity;
}

void Ball::bounceVertically()
{
    y = yVelocity < 0 ? ARENA_BOTTOM + WIDTH : ARENA_TOP;
    yVelocity = -yVelocity;
}
