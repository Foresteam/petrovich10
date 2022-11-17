#pragma once
#include <SFML/Graphics.hpp>
#include "../global.h"
#include "../HitboxRect.h"
#include <string>
#include <list>
#include <foresteamnd/Vector2>
using namespace std;

class Entity {
private:
	Vector2 _scale;
	Vector2 _pos;
	Vector2 _size;
protected:
	clock_t _movementLock;
public:
	bool onGround;
	HitboxRect hitbox;

	sf::Texture texture;
	sf::Sprite image;
	float mass = 0;
	Vector2 velocity;
	bool kinematic, background, transparent, enabled, collideWorld;

	Entity(string filename, Vector2 textureRectSize = Vector2());
	virtual ~Entity() = default;
	int MoveTo(const Vector2& npos);
	int Move(const Vector2& add);
	void SetImage(string filename);
	void Scale(const Vector2& scale);
	void Scale(const float& scale);
	void SetScale(const float& scale);
	void SetScale(const Vector2& scale);
	void SetColor(const sf::Color& color);
	void ApplyForce(const Vector2& force, const float& lockTime);
	bool GetMovementLocked();

	Vector2 GravitationVector();
	void Gravitate();
	void Collide(Entity& other);

	void Rotate(int direction, bool reversed);

	float GetW();
	float GetH();
	Vector2 GetPos();
	Vector2 GetScale();
	Vector2 GetSize();
	sf::Color GetColor();

	/// @returns true if the object is to be deleted
	virtual bool Update(list<Entity*>& objects);
	virtual void Draw(sf::RenderWindow& window);
	virtual bool CanCollide(Entity* other, Vector2 direction);
};