#pragma once
#include "Attacker.h"

class MeleeAttacker : public Attacker {
protected:
    float range;

	MeleeAttacker(float range, float attackPower, float attackAnimTime, float attackCooldown);

	void Attack(Object* attacker, int direction, list<Object*>& objects) override;
};