#include "Attacker.h"

Attacker::Attacker(float attackPower, float attackAnimTime, float attackCooldown) {
	this->attackPower = attackPower;
	this->attackAnimTime = attackAnimTime;
	this->attackCooldown = attackCooldown;
}

bool Attacker::AttackReset() {
	if (float(clock() - lastSwing) / CLOCKS_PER_SEC < attackAnimTime)
		return false;
	return true;
}
bool Attacker::AttackReady() {
	if (lastSwing == 0)
		return true;
	if (float(clock() - lastSwing) / CLOCKS_PER_SEC < attackAnimTime + attackCooldown)
		return false;
	lastSwing = 0;
	return true;
}