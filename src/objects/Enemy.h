#pragma once
#include "Object.h"
#include "../Healthy.h"

class Enemy : public Object, public Healthy {
public:
    Enemy();
    void TakeDamage(float amount) override;
    bool Update() override;
};