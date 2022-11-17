#include "MeleeAttack.h"
#include "../objects/Healthy.h"

MeleeAttack::MeleeAttack(float range, float verticalRangePlus, float attackPower, float attackAnimTime, float attackCooldown, float attackDelay) : Attack(attackPower, attackAnimTime, attackCooldown, attackDelay) {
	this->_range = range;
	this->_verticalRangePlus = verticalRangePlus;
	_knockback = 0;
}
void MeleeAttack::SetKnockback(float knockback) {
	_knockback = knockback;
}
sf::FloatRect MeleeAttack::GetZone(Object* attacker, int direction) {
	float x = attacker->GetPos().x, szx = _range;
	// 'Cause direction=0 means "both", not "none"
	if (direction)
		szx *= direction;
	else
		szx *= 2, x -= szx / 2;
	return sf::FloatRect(sf::Vector2f(x, attacker->GetPos().y - attacker->GetH() / 2 - _verticalRangePlus / 2), sf::Vector2f(szx, attacker->GetH() + _verticalRangePlus * 2));
}
void MeleeAttack::DoAttack(Object* attacker, int direction, list<Object*>& objects) {
	Attack::DoAttack(attacker, direction, objects);
	sf::FloatRect zone = GetZone(attacker, direction);

	for (Object* victim : objects)
		if (victim != attacker && instanceof<Healthy>(victim) && sf::FloatRect(v2f(victim->GetPos() - (victim->GetSize() / 2)), v2f(victim->GetSize())).intersects(zone)) {
			((Healthy*)victim)->TakeDamage(attackPower, attacker);
			if (_knockback) {
				auto knockback = (victim->GetPos() - attacker->GetPos()).Normalized() * _knockback;
				victim->ApplyForce(knockback, .3f);
			}
		}
}