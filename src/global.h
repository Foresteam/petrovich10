#pragma once
#include <SFML/Graphics.hpp>
#include <foresteamnd/Vector2>
#include "RandomSound.h"
#include <string>

#ifdef NDEBUG
	#define ASSETS std::string("assets/")
#else
	#define ASSETS std::string("../assets/")
#endif

const float G = 9.8, G_SCALE = 1.e-1;
const int FPS = 60;

const int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;

extern double deltaTime;
extern RandomSound aSwordSwingSound, aSwordSliceSound, aSwordExecuteSound;
extern sf::SoundBuffer wallBreakBuffer;
extern sf::Sound wallBreakSound;

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