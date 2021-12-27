#pragma once
#include <SFML/Graphics.hpp>
#include "../global.h"
#include "../HitboxRect.h"
#include <string>
#include <foresteamnd/Vector2>
using namespace std;

class Object {
private:
	Vector2 scale;
	Vector2 pos;
	Vector2 size;
protected:
	enum STATE { IDLE = 0, ATTACK };
	virtual void SetState(STATE state);
public:
	bool onGround;
	HitboxRect hitbox;

	sf::Texture texture;
	sf::Sprite image;
	float mass = 0;
	Vector2 velocity;
	bool kinematic, background, transparent;

	Object(string filename, Vector2 textureRectSize = Vector2());
	virtual ~Object();
	int MoveTo(const Vector2& npos);
	int Move(const Vector2& add);
	void setImage(string filename);
	void Scale(const Vector2& scale);

	float GetW();
	float GetH();
	Vector2 GetPos();
	Vector2 GetScale();
	Vector2 GetSize();

	/// @returns true if the object is to be deleted
	virtual bool Update();
	virtual void Draw(sf::RenderWindow& window);
};