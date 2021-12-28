#include "SpikeAttack.h"
#include "../objects/Healthy.h"

SpikeAttack::SpikeAttack(float height, float attackPower, float attackAnimTime, float attackCooldown, float attackDelay) : Attack(attackPower, attackAnimTime, attackCooldown, attackDelay) {
    this->height = height;
}

void SpikeAttack::DoAttack(Object* attacker, int direction, list<Object*>& objects) {
	Attack::DoAttack(attacker, direction, objects);
	sf::FloatRect hitbox = sf::FloatRect(sf::Vector2f(0, window_height - height), sf::Vector2f(window_width, height));

    for (Object* o : objects)
        if (o != attacker && instanceof<Healthy>(o) && hitbox.intersects(o->image.getGlobalBounds()))
            ((Healthy*)(o))->TakeDamage(attackPower, attacker);
}