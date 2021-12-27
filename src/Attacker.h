#pragma once
#include "objects/Object.h"
#include <list>

class Attacker {
protected:
	const float ATTACK_COOLDOWN = .3f;
	const float AP = 10;
	clock_t lastSwing = 0;

	virtual void Attack(Object* attacker, int direction, list<Object*>& objects) = 0;
	bool AttackReset();
};