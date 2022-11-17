#pragma once
#include <SFML/Graphics.hpp>
#include <foresteamnd/Vector2>
#include "sound/RandomSound.h"
#include <string>
#include <list>

extern std::string EXE_PATH;

#ifdef DEBUG
	#define ASSETS EXE_PATH + "/../assets/"
#else
	#define ASSETS EXE_PATH + "/assets/"
#endif

const float G = 9.8, G_SCALE = .8e+3f;
const float BASE_JUMP_POWER = G * G_SCALE / 4.5f;
const int FPS = 60;

const int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;

extern double deltaTime;
extern RandomSound aSwordSwingSound, aSwordSliceSound, aSwordExecuteSound, aPunchSound, anAirWaveSound;
extern std::list<Sound**> globalSounds;
extern sf::SoundBuffer wallBreakBuffer;
extern sf::Sound wallBreakSound;

float CalcJumpPower(Vector2 scale, float mass = 1, float boost = 1);

// struct Shared {
// 	Player* me;
// 	list<Object*> objects;
// 	clock_t lastUpdate;
// };

Vector2 f2v(const sf::Vector2f& vec);
sf::Vector2f v2f(const Vector2& vec);
Vector2 i2v(const sf::Vector2i& vec);
sf::Vector2i v2i(const Vector2& vec);

template <typename Base, typename T>
inline bool instanceof (const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}