#include "SpikeAttack.h"
#include "../entities/Healthy.h"

SpikeAttack::SpikeAttack(float height, float attackPower, float attackAnimTime, float attackCooldown, float attackDelay) : Attack(attackPower, attackAnimTime, attackCooldown, attackDelay) {
    this->height = height;
}

void SpikeAttack::DoAttack(Entity* attacker, int direction, list<Entity*>& objects) {
	Attack::DoAttack(attacker, direction, objects);
	sf::FloatRect hitbox = sf::FloatRect(sf::Vector2f(0, WINDOW_HEIGHT - height), sf::Vector2f(WINDOW_WIDTH, height));

    for (Entity* o : objects)
        if (o != attacker && instanceof<Healthy>(o) && hitbox.intersects(o->image.getGlobalBounds()))
            ((Healthy*)(o))->TakeDamage(attackPower, attacker);
}