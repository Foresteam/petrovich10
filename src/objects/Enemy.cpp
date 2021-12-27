#include "Enemy.h"

Enemy::Enemy() : Healthy(100, "../assets/enemy.png") {
    mass = .5;
	InitHealthBar();
}

void Enemy::TakeDamage(float amount) {
    SetHP(HP() - amount);
}

bool Enemy::Update() {
    Healthy::Update();
    return !Alive();
}