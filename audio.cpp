#include "audio.h"

Audio::Audio()
{
    bounceBuffer = sf::SoundBuffer();
}

bool Audio::loadBounce()
{
    if (bounceBuffer.loadFromFile("resources/Bounce.ogg"))
    {
        bounce.setBuffer(bounceBuffer);
        return true;
    }
    return false;
}

bool Audio::loadWhoosh()
{
    if (whooshBuffer.loadFromFile("resources/AI_FIRE2.ogg"))
    {
        whoosh.setBuffer(whooshBuffer);
        return true;
    }
    return false;
}

bool Audio::loadBGM()
{
    if (!bgm.openFromFile("resources/Android.ogg"))
    {
        return false;
    }
    bgm.setLoop(true);
    return true;
}

void Audio::playBounce()
{
    bounce.play();
}

void Audio::playWhoosh()
{
    whoosh.play();
}

void Audio::playBGM()
{
    bgm.play();
}

void Audio::stopBGM()
{
    bgm.stop();
}
