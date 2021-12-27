#pragma once
#include "Object.h"
#include "Healthy.h"
#include "../MeleeAttacker.h"

class Enemy : public Healthy, private MeleeAttacker {
private:
	static Vector2 IMG_SIZE;
	enum STATE { IDLE = 1, ATTACK = 0 };
    bool isSeeingPlayer;
    int direction;
public:
    Enemy();
    void TakeDamage(float amount) override;
	bool Update(list<Object*>& objects) override;
    void SetState(STATE state);
};