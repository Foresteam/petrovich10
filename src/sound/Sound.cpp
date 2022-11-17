#include "Sound.h"

Sound::Sound(bool ingame, std::string start, std::string loop, std::string end) {
	_lastPlayed = -1;

	_buffers = std::vector<sf::SoundBuffer*>();
	_sounds = std::vector<sf::Sound*>();

	_buffers.push_back(new sf::SoundBuffer());
	_buffers.back()->loadFromFile(start);
	_sounds.push_back(new sf::Sound(*_buffers.back()));

	if (loop.length() > 0) {
		_buffers.push_back(new sf::SoundBuffer());
		_buffers.back()->loadFromFile(loop);
		_sounds.push_back(new sf::Sound(*_buffers.back()));
		_sounds.back()->setLoop(true);
	}
	if (end.length() > 0) {
		_buffers.push_back(new sf::SoundBuffer());
		_buffers.back()->loadFromFile(end);
		_sounds.push_back(new sf::Sound(*_buffers.back()));
	}
}
Sound::~Sound() {
	while (!_sounds.empty())
		delete _sounds.back(), _sounds.pop_back();
	while (!_buffers.empty())
		delete _buffers.back(), _buffers.pop_back();
}

void Sound::Play() {
	if (_lastPlayed >= 0 && _sounds[_lastPlayed]->getStatus() == sf::Sound::Status::Paused) {
		_sounds[_lastPlayed]->play();
		return;
	}
	Stop();
	_lastPlayed = 0;
	_sounds[_lastPlayed]->play();
	printf("PLAY %i\n", _lastPlayed);
}
void Sound::Stop() {
	for (auto& sound : _sounds)
		if (sound->getStatus() != sf::Sound::Status::Stopped)
			sound->stop();
}
void Sound::Pause() {
	if (_lastPlayed >= 0)
		_sounds[_lastPlayed]->pause();
}
bool Sound::EndLoop() {
	if (GetStatus() < STATUS::BEGIN || GetStatus() == STATUS::END)
		return false;
	_sounds[_lastPlayed]->stop();
	if (GetStatus() == STATUS::BEGIN)
		_lastPlayed++;
	return true;
}
Sound::STATUS Sound::GetStatus() {
	if (_sounds[0]->getStatus() == sf::Sound::Status::Playing)
		return STATUS::BEGIN;
	if (_sounds.size() > 1 && _sounds[1]->getStatus() == sf::Sound::Status::Playing)
		return STATUS::LOOP;
	if (_sounds.size() > 2 && _sounds[2]->getStatus() == sf::Sound::Status::Playing)
		return STATUS::END;
	for (auto& sound : _sounds)
		if (sound->getStatus() == sf::Sound::Status::Paused)
			return STATUS::PAUSED;
	return STATUS::NOT_PLAYING;
}
bool Sound::IsPlaying() {
	return GetStatus() != STATUS::NOT_PLAYING && GetStatus() != STATUS::PAUSED;
}
void Sound::Update() {
	if (GetStatus() != STATUS::NOT_PLAYING)
		return;
	if (_lastPlayed + 1 >= _sounds.size())
		return;
	_lastPlayed++;
	_sounds[_lastPlayed]->play();
}