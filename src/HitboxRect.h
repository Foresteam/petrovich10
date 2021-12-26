#pragma once
#include <foresteamnd/Vector2>
#include <SFML/Graphics.hpp>

class HitboxRect {
public:
	Vector2* pos;
	Vector2* size;
	HitboxRect(Vector2* pos, Vector2* size);
	HitboxRect() : HitboxRect(nullptr, nullptr) {}
	sf::FloatRect GetRect();
	Vector2 GetPushOutVector(const HitboxRect& other) const;
};