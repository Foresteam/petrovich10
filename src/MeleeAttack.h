#pragma once
#include "Attack.h"

class MeleeAttack : public Attack {
protected:
	float range, verticalRangePlus;
public:
	MeleeAttack(float range, float verticalRangePlus, float attackPower, float attackAnimTime, float attackCooldown, float attackDelay = 0);

	void DoAttack(Object* attacker, int direction, list<Object*>& objects) override;

	sf::FloatRect GetZone(Object* attacker, int direction);
};