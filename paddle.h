#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
public:
    Paddle(float initialLeft, float initialTop);

    float left();

    float right();
    float top();

    float bottom();

    void pushUp(float elapsed);

    void pushDown(float elapsed);

    void updateFrame(float elapsed);

    void draw();

    float paddleLeft;
    float paddleTop;
    float velocity;
    static const float TOP_WALL_HEIGHT;
    static const float BOTTOM_WALL_HEIGHT;
    static const float HEIGHT;
    static const float SPEED;
    static const float ARENA_LEVEL;
    static const float WIDTH;
};


#endif // PADDLE_H
