#pragma once
#include "Attacker.h"

class MeleeAttacker : public Attacker {
protected:
    float range;

    MeleeAttacker(float range);

    void Attack(Object* attacker, int direction, list<Object*>& objects) override;
};