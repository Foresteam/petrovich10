#pragma once
#include "objects/Object.h"
#include <list>

class Attack {
protected:
	float attackAnimTime, attackCooldown, attackPower, attackDelay;
	clock_t lastSwing = 0, delayWait = 0;
public:
	Attack(float attackPower, float attackAnimTime, float attackCooldown, float attackDelay = 0);

	virtual void DoAttack(Object* attacker, int direction, list<Object*>& objects) = 0;
	void Prepare();
	bool Prepared();
	bool Ready();
	bool Reset();
};