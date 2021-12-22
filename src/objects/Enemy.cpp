#include "Enemy.h"

Enemy::Enemy() : Object("../assets/enemy.png"), Healthy(100) {
    mass = 1;
}

void Enemy::TakeDamage(float amount) {
    SetHP(HP() - amount);
}

bool Enemy::Update() {
    return !Alive() && (gonnaBeDeleted = true);
}