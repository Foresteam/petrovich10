#include "MeleeAttacker.h"
#include "objects/Healthy.h"

MeleeAttacker::MeleeAttacker(float range) {
    this->range = range;
}
void MeleeAttacker::Attack(Object* attacker, int direction, list<Object*>& objects) {
	lastSwing = clock();
	sf::FloatRect zone = sf::FloatRect(sf::Vector2f(attacker->GetPos().x, attacker->GetPos().y - attacker->GetH() / 2), sf::Vector2f(range * direction, attacker->GetH()));

	for (Object* o : objects)
		if (instanceof <Healthy>(o) && o != attacker && sf::FloatRect(v2f(o->GetPos() - (o->GetSize() / 2)), v2f(o->GetSize())).intersects(zone))
			((Healthy*)o)->TakeDamage(10);
}