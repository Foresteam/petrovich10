#pragma once
#include "Object.h"
#include "Healthy.h"

class HealthBar : public Object {
private:
    Healthy* parent;
    static Vector2 IMG_SIZE;
    Object* _background;
public:
    ~HealthBar();
	HealthBar(Healthy* parent, float scale);
	bool Update(list<Object*>& objects) override;
    void Draw(sf::RenderWindow& window) override;
};