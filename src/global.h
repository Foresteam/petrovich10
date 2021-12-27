#pragma once
#include <SFML/Graphics.hpp>
#include <foresteamnd/Vector2>

const float G = 9.8, G_SCALE = 1.e-4;
const int FPS = 60;

const int window_width = 1280, window_height = 720;

extern float deltaTime;

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