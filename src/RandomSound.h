#pragma once
#include <SFML/Audio.hpp>

class RandomSound {
private:
    int count;
    sf::SoundBuffer* buffers;
    sf::Sound* sounds;
public:
    ~RandomSound();
    RandomSound(std::string pathBegin, std::string pathEnd, int count);
    void Play();
};