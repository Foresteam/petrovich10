#include "Vadid.h"
#include "Player.h"

Vadid::Vadid(float kDamage) : Healthy(150, "../assets/textures/boss.png", RECT_SIZE) {

}

void Vadid::TakeDamage(float amount, Object* source) {
	Healthy::TakeDamage(amount, source);
    if (instanceof<Player>(source))
        if (!Alive())
            aSwordExecuteSound.Play();
        else
            aSwordSliceSound.Play();
}

Vector2 Vadid::RECT_SIZE = Vector2(253, 262);