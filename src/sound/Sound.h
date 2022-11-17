#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class Sound {
public:
	enum STATUS { NOT_PLAYING = 0, PAUSED, BEGIN, LOOP, END };
private:
	std::vector<sf::SoundBuffer*> _buffers;
	std::vector<sf::Sound*> _sounds;
	int _lastPlayed;
	bool _ingame;
public:
	Sound(bool ingame, std::string start, std::string loop = "", std::string end = "");
	~Sound();

	void Stop();
	void Pause();
	void Play();
	bool EndLoop();

	STATUS GetStatus();
	bool IsPlaying();
	bool IsIngame();

	void Update();
};