#include "SpikeAttack.h"

SpikeAttack::SpikeAttack(float height, float attackPower, float attackAnimTime, float attackCooldown, float attackDelay) : Attack(attackPower, attackAnimTime, attackCooldown, attackDelay) {
    this->height = height;
}

void SpikeAttack::DoAttack(Object* attacker, int direction, list<Object*>& objects) {

}