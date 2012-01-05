#include "audio.h"

Audio::Audio()
{
    bounceBuffer = sf::SoundBuffer();
}

bool Audio::loadBounce()
{
    if (bounceBuffer.LoadFromFile("resources/Bounce.ogg"))
    {
        bounce.SetBuffer(bounceBuffer);
        return true;
    }
    return false;
}

bool Audio::loadWhoosh()
{
    if (whooshBuffer.LoadFromFile("resources/AI_FIRE2.ogg"))
    {
        whoosh.SetBuffer(whooshBuffer);
        return true;
    }
    return false;
}

bool Audio::loadBGM()
{
    if (!bgm.OpenFromFile("resources/Android.ogg"))
    {
        return false;
    }
    bgm.SetLoop(true);
    return true;
}

void Audio::playBounce()
{
    bounce.Play();
}

void Audio::playWhoosh()
{
    whoosh.Play();
}

void Audio::playBGM()
{
    bgm.Play();
}

void Audio::stopBGM()
{
    bgm.Stop();
}
