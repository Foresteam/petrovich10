#pragma once
#include "Object.h"

class Healthy : public Object {
protected:
    float hp, maxHP;
    Object* healthBar;
public:
	Healthy(float maxHP, string file, Vector2 imgsz = Vector2());
    ~Healthy();
	float HP();
    float MaxHP();
    void SetHP(float val);
    bool Alive();
	virtual void TakeDamage(float amount) = 0;
    void Draw(sf::RenderWindow& window) override;
    void InitHealthBar();
    bool Update() override;
};