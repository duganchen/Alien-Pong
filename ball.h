#ifndef ALIENPONG_BALL_H
#define ALIENPONG_BALL_H


class Ball
{
public:
    Ball();

    float top();

    float bottom();

    float left();
    float right();

    bool isLeftBound();
    bool isRightBound();

    void moveToCenter();
    void draw();
    void updateFrame(float elapsed);
    void bounceHorizontally();

    void bounceVertically();
    float speed();
private:
    constexpr static const float ARENA_LEVEL = 3;
    constexpr static const float WIDTH = 0.1f;
    constexpr static const float MIDDLE_X = 1.5f;
    constexpr static const float SPEED = 1.0f;
    float xVelocity;
    float yVelocity;
    float y;
    float x;

    constexpr static const float ARENA_TOP = 1;
    constexpr static const float ARENA_BOTTOM = -1;
    constexpr static const float ARENA_LEFT = 0.1f;
    constexpr static const float ARENA_RIGHT = 2.9f;
};

#endif
