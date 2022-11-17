#pragma once
#include "Entity.h"
#include "Healthy.h"
#include "../attacks/MeleeAttack.h"

class Nikita : public Healthy {
private:
	static Vector2 RECT_SIZE;
	enum STATE { IDLE = 1, ATTACK = 0 };
    bool isSeeingPlayer;
    int direction;
    MeleeAttack* attack;
public:
    Nikita();
    ~Nikita();
    void TakeDamage(float amount, Entity* source) override;
	bool Update(list<Entity*>& objects) override;
    void SetState(STATE state);
};