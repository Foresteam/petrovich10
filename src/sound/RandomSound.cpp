#include "RandomSound.h"
#include <foresteamnd/Utils>

RandomSound::~RandomSound() {
	for (auto sound = _sounds; sound != _sounds + _count; sound++)
		delete *sound;
	delete[] _sounds;
}
RandomSound::RandomSound(std::string pathBegin, std::string pathEnd, int count, bool ingame) {
	this->_count = count;
	_sounds = new Sound*[count];
	for (int i = 0; i < count; i++)
		_sounds[i] = new Sound(ingame, pathBegin + Utils::String::Convert(i + 1) + pathEnd);
}
void RandomSound::Play() {
	int i = (int)(Utils::RandRange(0, _count));
	_sounds[i]->Play();
}