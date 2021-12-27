#pragma once
#include "Object.h"

class Healthy : public Object {
protected:
    float hp, maxHP;
    Object* healthBar;
public:
	Healthy(float maxHP, string file, Vector2 imgsz = Vector2());
    ~Healthy() override;
	float HP();
    float MaxHP();
    void SetHP(float val);
    bool Alive();
    /// @returns Is fatal
	virtual bool TakeDamage(float amount);
    void Draw(sf::RenderWindow& window) override;
    void InitHealthBar();
    bool Update() override;
};