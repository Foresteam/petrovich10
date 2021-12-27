#include "MeleeAttacker.h"
#include "objects/Healthy.h"

MeleeAttacker::MeleeAttacker(float range, float attackPower, float attackAnimTime, float attackCooldown) : Attacker(attackPower, attackAnimTime, attackCooldown) {
	this->range = range;
}
void MeleeAttacker::Attack(Object* attacker, int direction, list<Object*>& objects) {
	lastSwing = clock();
	float x = attacker->GetPos().x, szx = range;
	// 'Cause direction=0 means "both", not "none"
	if (direction)
		szx *= direction;
	else
		szx *= 2, x -= szx / 2;
	sf::FloatRect zone = sf::FloatRect(sf::Vector2f(x, attacker->GetPos().y - attacker->GetH() / 2), sf::Vector2f(szx, attacker->GetH()));

	for (Object* o : objects)
		if (instanceof <Healthy>(o) && o != attacker && sf::FloatRect(v2f(o->GetPos() - (o->GetSize() / 2)), v2f(o->GetSize())).intersects(zone))
			((Healthy*)o)->TakeDamage(10);
}