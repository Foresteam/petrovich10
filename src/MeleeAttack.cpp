#include "MeleeAttack.h"
#include "objects/Healthy.h"

MeleeAttack::MeleeAttack(float range, float verticalRangePlus, float attackPower, float attackAnimTime, float attackCooldown, float attackDelay) : Attack(attackPower, attackAnimTime, attackCooldown, attackDelay) {
	this->range = range;
	this->verticalRangePlus = verticalRangePlus;
}
sf::FloatRect MeleeAttack::GetZone(Object* attacker, int direction) {
	float x = attacker->GetPos().x, szx = range;
	// 'Cause direction=0 means "both", not "none"
	if (direction)
		szx *= direction;
	else
		szx *= 2, x -= szx / 2;
	return sf::FloatRect(sf::Vector2f(x, attacker->GetPos().y - attacker->GetH() / 2 - verticalRangePlus / 2), sf::Vector2f(szx, attacker->GetH() + verticalRangePlus * 2));
}
void MeleeAttack::DoAttack(Object* attacker, int direction, list<Object*>& objects) {
	lastSwing = clock();
	sf::FloatRect zone = GetZone(attacker, direction);

	for (Object* o : objects)
		if (instanceof <Healthy>(o) && o != attacker && sf::FloatRect(v2f(o->GetPos() - (o->GetSize() / 2)), v2f(o->GetSize())).intersects(zone))
			((Healthy*)o)->TakeDamage(attackPower);
}