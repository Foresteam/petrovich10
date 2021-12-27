#include "Attacker.h"

bool Attacker::AttackReset() {
	if (lastSwing == 0)
		return true;
	if (float(clock() - lastSwing) / CLOCKS_PER_SEC < ATTACK_COOLDOWN)
		return false;
	lastSwing = 0;
	return true;
}