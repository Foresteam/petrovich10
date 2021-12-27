#include "Enemy.h"
#include "../global.h"

Enemy::Enemy() : Healthy(100, "../assets/textures/enemy.png") {
    mass = .5;
	InitHealthBar();
}

bool Enemy::TakeDamage(float amount) {
    bool rs = Healthy::TakeDamage(amount);
    if (rs)
        aSwordExecuteSound.Play();
    else
        aSwordSliceSound.Play();
    return rs;
}

bool Enemy::Update() {
    Healthy::Update();
    return !Alive();
}