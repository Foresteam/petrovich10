#pragma once
#include "objects/Object.h"
#include <list>

class Attacker {
protected:
	float attackAnimTime, attackCooldown, attackPower;
	clock_t lastSwing = 0;

	Attacker(float attackPower, float attackAnimTime, float attackCooldown);

	virtual void Attack(Object* attacker, int direction, list<Object*>& objects) = 0;
	bool AttackReady();
	bool AttackReset();
};