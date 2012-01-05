#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>

class Audio
{
public:
    Audio();
    bool loadBounce();
    bool loadWhoosh();
    void playBounce();
    void playWhoosh();
    void playBGM();
    bool loadBGM();
    void stopBGM();
private:
    sf::SoundBuffer bounceBuffer;
    sf::SoundBuffer whooshBuffer;
    sf::Sound bounce;
    sf::Sound whoosh;
    sf::Music bgm;
};

#endif // AUDIO_H
