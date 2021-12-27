#include "Enemy.h"
#include "../global.h"

Enemy::Enemy() : Healthy(100, "../assets/textures/enemy.png") {
    mass = .5;
	InitHealthBar();
}

void Enemy::TakeDamage(float amount) {
    Healthy::TakeDamage(amount);
    if (!Alive())
        aSwordExecuteSound.Play();
    else
        aSwordSliceSound.Play();
}

bool Enemy::Update(list<Object*>& objects) {

	Healthy::Update(objects);
    return !Alive();
}