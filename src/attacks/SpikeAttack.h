#pragma once
#include "Attack.h"

class SpikeAttack : public Attack {
private:
    float height;
public:
    SpikeAttack(float height, float attackPower, float attackAnimTime, float attackCooldown, float attackDelay = 0);

	void DoAttack(Entity* attacker, int direction, list<Entity*>& objects) override;
};