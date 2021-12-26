#pragma once
#include "Object.h"

class Healthy : public Object {
protected:
    float hp, maxHP;
public:
	Healthy(float maxHP, string file, Vector2 imgsz = Vector2());
	float HP();
    float MaxHP();
    void SetHP(float val);
    bool Alive();
};