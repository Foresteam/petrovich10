#include "Attacker.h"

Attacker::Attacker(float attackPower, float attackAnimTime, float attackCooldown, float attackDelay) {
	this->attackPower = attackPower;
	this->attackAnimTime = attackAnimTime;
	this->attackCooldown = attackCooldown;
	this->attackDelay = attackDelay;
}

bool Attacker::AttackReset() {
	if (float(clock() - lastSwing) / CLOCKS_PER_SEC < attackAnimTime)
		return false;
	return true;
}
void Attacker::AttackPrepare() {
	delayWait = clock();
}
bool Attacker::AttackPrepared() {
	return !(float(clock() - delayWait) / CLOCKS_PER_SEC < attackDelay);
}

bool Attacker::AttackReady() {
	if (lastSwing == 0)
		return true;
	if (float(clock() - lastSwing) / CLOCKS_PER_SEC < attackAnimTime + attackCooldown)
		return false;
	lastSwing = 0;
	return true;
}
