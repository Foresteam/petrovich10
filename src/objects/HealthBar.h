#pragma once
#include "Object.h"
#include "../Healthy.h"

class HealthBar : public Object {
private:
    Healthy* hparent;
    Object* oparent;
    static Vector2 IMG_SIZE;
public:
	HealthBar(Healthy* hparent, Object* oparent, float scale);
	bool Update() override;
};