#pragma once
#include "Object.h"
#include "Healthy.h"

class Enemy : public Healthy {
public:
    Enemy();
    bool TakeDamage(float amount) override;
    bool Update() override;
};