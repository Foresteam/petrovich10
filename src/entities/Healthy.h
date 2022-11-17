#pragma once
#include "Entity.h"

class Healthy : public Entity {
protected:
    float hp, maxHP;
    Entity* healthBar;
public:
	Healthy(float maxHP, string file, Vector2 imgsz = Vector2());
    ~Healthy() override;
	float HP();
    float MaxHP();
    void SetHP(float val);
    bool Alive();
    /// @returns Is fatal
	virtual void TakeDamage(float amount, Entity* source);
    void Draw(sf::RenderWindow& window) override;
    void InitHealthBar();
	bool Update(list<Entity*>& objects) override;
};