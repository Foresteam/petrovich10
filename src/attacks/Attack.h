#pragma once
#include "../objects/Object.h"
#include <list>

class Attack {
protected:
	float attackAnimTime, attackCooldown, attackPower, attackDelay;
	clock_t lastSwing, delayWait;
public:
	Attack(float attackPower, float attackAnimTime, float attackCooldown, float attackDelay = 0);

	virtual void DoAttack(Object* attacker, int direction, list<Object*>& objects);
	float GetPower();
	void Prepare();
	bool Prepared();
	bool Ready();
	bool Reset();
};