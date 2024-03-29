#pragma once
#include "Attack.h"

class MeleeAttack : public Attack {
protected:
	float _range, _verticalRangePlus, _knockback;
public:
	MeleeAttack(float range, float verticalRangePlus, float attackPower, float attackAnimTime, float attackCooldown, float attackDelay = 0);

	void DoAttack(Entity* attacker, int direction, list<Entity*>& objects) override;

	void SetKnockback(float knockback);
	sf::FloatRect GetZone(Entity* attacker, int direction = 0);
};