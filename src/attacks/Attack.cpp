#include "Attack.h"

Attack::Attack(float attackPower, float attackAnimTime, float attackCooldown, float attackDelay) {
	this->attackPower = attackPower;
	this->attackAnimTime = attackAnimTime;
	this->attackCooldown = attackCooldown;
	this->attackDelay = attackDelay;
	delayWait = 0;
	lastSwing = 0;
}

bool Attack::Reset() {
	if (float(clock() - lastSwing) / CLOCKS_PER_SEC < attackAnimTime)
		return false;
	return true;
}
void Attack::Prepare() {
	delayWait = clock();
}
bool Attack::Prepared() {
	return float(clock() - delayWait) / CLOCKS_PER_SEC >= attackDelay;
}

bool Attack::Ready() {
	if (lastSwing == 0)
		return true;
	if (float(clock() - lastSwing) / CLOCKS_PER_SEC < attackAnimTime + attackCooldown)
		return false;
	lastSwing = 0;
	return true;
}

void Attack::DoAttack(Entity* attacker, int direction, list<Entity*>& objects) {
	lastSwing = clock();
}

float Attack::GetPower() {
	return attackPower;
}