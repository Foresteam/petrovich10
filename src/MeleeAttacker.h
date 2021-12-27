#pragma once
#include "Attacker.h"

class MeleeAttacker : public Attacker {
protected:
	float range, verticalRangePlus;

	MeleeAttacker(float range, float verticalRangePlus, float attackPower, float attackAnimTime, float attackCooldown, float attackDelay = 0);

	void Attack(Object* attacker, int direction, list<Object*>& objects) override;

	sf::FloatRect GetZone(Object* attacker, int direction);
};