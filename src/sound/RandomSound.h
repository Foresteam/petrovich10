#pragma once
#include "Sound.h"

class RandomSound {
private:
    Sound** _sounds;
		int _count;
public:
    ~RandomSound();
    RandomSound(std::string pathBegin, std::string pathEnd, int count, bool ingame = true);
    void Play();
};