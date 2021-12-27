#pragma once
#include "Object.h"
#include "Healthy.h"

class Enemy : public Healthy {
private:
    enum STATE { IDLE, ATTACK };
public:
    Enemy();
    void TakeDamage(float amount) override;
	bool Update(list<Object*>& objects) override;
};