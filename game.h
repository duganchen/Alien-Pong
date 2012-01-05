#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "ball.h"

class Game
{
public:
    void play(int width, int height, int particleCount, float particleSize, int planetType);
    static const int MIRROR = 0;
    static const int FIRE = 1;
    static const int GAS = 2;
    static const int SAPPHIRE = 3;
};

#endif // GAME_H
