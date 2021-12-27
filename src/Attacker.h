#pragma once
#include "objects/Object.h"
#include <list>

class Attacker {
protected:
	float attackAnimTime, attackCooldown, attackPower, attackDelay;
	clock_t lastSwing = 0, delayWait = 0;

	Attacker(float attackPower, float attackAnimTime, float attackCooldown, float attackDelay = 0);

	virtual void Attack(Object* attacker, int direction, list<Object*>& objects) = 0;
	void AttackPrepare();
	bool AttackPrepared();
	bool AttackReady();
	bool AttackReset();
};