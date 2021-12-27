#include "Wall.h"

Wall::Wall() : Healthy(500, "../assets/textures/wall.png") {
    mass = 500;
    // kinematic = true;
    Scale(Vector2(.6f));
    InitHealthBar();

    hitBuffer.loadFromFile("../assets/sounds/sword_hits_wall.ogg");
    hitSound.setBuffer(hitBuffer);
}

void Wall::TakeDamage(float amount) {
    Healthy::TakeDamage(amount);
    if (amount > 0)
        hitSound.play();
}