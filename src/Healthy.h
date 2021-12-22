#pragma once

class Healthy {
protected:
    float hp, maxHP;
public:
    Healthy(float maxHP);
    float HP();
    float MaxHP();
    void SetHP(float val);
    bool Alive();
};