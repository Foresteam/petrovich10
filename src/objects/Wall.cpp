#include "Wall.h"

Wall::Wall() : Healthy(100, "../assets/textures/wall.png") {
    mass = 500;
    // kinematic = true;
    Scale(Vector2(.6f));
    InitHealthBar();

    hitBuffer.loadFromFile("../assets/sounds/sword_hits_wall.ogg");
    hitSound.setBuffer(hitBuffer);
}

void Wall::TakeDamage(float amount, Object* source) {
	Healthy::TakeDamage(amount, source);
	if (Alive())
        hitSound.play();
    else
        wallBreakSound.play();
}