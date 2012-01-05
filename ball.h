#ifndef BALL_H
#define BALL_H


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
    static const float ARENA_LEVEL = 3;
    static const float WIDTH = 0.1f;
    static const float MIDDLE_X = 1.5f;
    //static const float SPEED = 0.005f;
    static const float SPEED = 1.0f;
    float xVelocity;
    float yVelocity;
    float y;
    float x;

        static const float ARENA_TOP = 1;
    static const float ARENA_BOTTOM = -1;
    static const float ARENA_LEFT = 0.1f;
    static const float ARENA_RIGHT = 2.9f;
};

#endif // BALL_H
