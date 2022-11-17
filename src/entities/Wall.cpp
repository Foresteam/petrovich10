#include "Wall.h"
#include "Nikita.h"
#include "Player.h"
#include "Vadid/Vadid.h"

Wall::Wall() : Healthy(100, ASSETS + "textures/wall.png") {
    mass = 500;
    // kinematic = true;
    Scale(Vector2(.6f));
    InitHealthBar();

    hitBuffer.loadFromFile(ASSETS + "sounds/sword_hits_wall.ogg");
    hitSound.setBuffer(hitBuffer);
}

void Wall::TakeDamage(float amount, Entity* source) {
	if (instanceof<Rasengan>(source))
		amount /= 4;
	Healthy::TakeDamage(amount, source);
	if (Alive()) {
		if (instanceof<Player>(source) || instanceof<Nikita>(source))
			hitSound.play();
		else if (instanceof<Vadid>(source))
			aPunchSound.Play();
		else if (instanceof<Rasengan>(source))
			anAirWaveSound.Play();
	}
	else
		wallBreakSound.play();
}