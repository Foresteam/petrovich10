#pragma once
#include <SFML/Graphics.hpp>
#include "../global.h"
#include "../HitboxRect.h"
#include <string>
#include <list>
#include <foresteamnd/Vector2>
using namespace std;

class Object {
private:
	Vector2 _scale;
	Vector2 _pos;
	Vector2 _size;
public:
	bool onGround;
	HitboxRect hitbox;

	sf::Texture texture;
	sf::Sprite image;
	float mass = 0;
	Vector2 velocity;
	bool kinematic, background, transparent, enabled;

	Object(string filename, Vector2 textureRectSize = Vector2());
	virtual ~Object();
	int MoveTo(const Vector2& npos);
	int Move(const Vector2& add);
	void SetImage(string filename);
	void Scale(const Vector2& scale);

	Vector2 GravitationVector();
	void Gravitate();
	void Collide(Object& other);

	void Rotate(int direction, bool reversed);

	float GetW();
	float GetH();
	Vector2 GetPos();
	Vector2 GetScale();
	Vector2 GetSize();

	/// @returns true if the object is to be deleted
	virtual bool Update(list<Object*>& objects);
	virtual void Draw(sf::RenderWindow& window);
};