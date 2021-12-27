#include "RandomSound.h"
#include <foresteamnd/Utils>
#include <chrono>
#include <thread>

RandomSound::~RandomSound() {
    delete[] buffers;
    delete[] sounds;
}
RandomSound::RandomSound(std::string pathBegin, std::string pathEnd, int count) {
    this->count = count;
    buffers = new sf::SoundBuffer[count]();
    sounds = new sf::Sound[count]();
    for (int i = 0; i < count; i++) {
        buffers[i].loadFromFile(pathBegin + Utils::String::Convert(i + 1) + pathEnd);
        sounds[i].setBuffer(buffers[i]);
	}
}
void RandomSound::Play() {
    int i = (int)(Utils::RandRange(0, count));
    sounds[i].play();
}