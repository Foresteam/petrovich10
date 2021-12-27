#pragma once
#include "Object.h"
#include "Healthy.h"
#include "../MeleeAttack.h"

class Nikita : public Healthy {
private:
	static Vector2 IMG_SIZE;
	enum STATE { IDLE = 1, ATTACK = 0 };
    bool isSeeingPlayer;
    int direction;
    MeleeAttack* attack;
public:
    Nikita();
    ~Nikita();
    void TakeDamage(float amount, Object* source) override;
	bool Update(list<Object*>& objects) override;
    void SetState(STATE state);
};