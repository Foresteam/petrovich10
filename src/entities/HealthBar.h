#pragma once
#include "Overlay.h"
#include "Healthy.h"

class HealthBar : public Overlay {
private:
    Healthy* parent;
    static Vector2 IMG_SIZE;
    Entity* _background;
public:
    ~HealthBar();
	HealthBar(Healthy* parent, float scale);
	bool Update(list<Entity*>& objects) override;
    void Draw(sf::RenderWindow& window) override;
};