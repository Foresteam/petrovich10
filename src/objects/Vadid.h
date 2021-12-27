#pragma once
#include "Healthy.h"
#include "../SpikeAttack.h"
#include "../MeleeAttack.h"

class Vadid : public Healthy {
private:
	static Vector2 RECT_SIZE;
	enum STATE { IDLE = 0, ATTACK = 3, JUMP_ATTACK };
	int direction;
	MeleeAttack* collideAttack;
    SpikeAttack* spikeAttack;

public:
	Vadid(float kDamage);
	~Vadid();
	void TakeDamage(float amount, Object* source) override;
	bool Update(list<Object*>& objects) override;
	void SetState(STATE state);
};