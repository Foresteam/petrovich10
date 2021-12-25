#pragma once
#include "objects/Object.h"

class Healthy : public Object {
protected:
    float hp, maxHP;
public:
    Healthy(std::string file, Vector2 imgsz, float maxHP);
    Healthy(std::string file, float maxHP);
    float HP();
    float MaxHP();
    void SetHP(float val);
    bool Alive();
};