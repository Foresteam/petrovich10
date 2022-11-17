#pragma once
#include "../Entity.h"
#include "../../attacks/MeleeAttack.h"

class Rasengan : public Entity {
private:
	const float INITIAL_SCALE = .1f, MAX_SCALE = .5f, GROW_DISTANCE = 700, RPS = 1.f;
	bool _destroy, _grewMax;
	MeleeAttack* _attack;
	Vector2 _startPos;
	Sound* _lifeSound;
public:
	Rasengan(Vector2 pos, Vector2 velocity, float damage);
	~Rasengan() override;
	void Draw(sf::RenderWindow& window) override;
	bool CanCollide(Entity* other, Vector2 direction) override;
	bool Update(list<Entity*>& objects) override;
};