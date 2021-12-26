#pragma once
#include "Object.h"
#include "Healthy.h"

class HealthBar : public Object {
private:
    Healthy* parent;
    static Vector2 IMG_SIZE;
public:
	HealthBar(Healthy* parent, float scale);
	bool Update() override;
};