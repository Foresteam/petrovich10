#include "HealthBar.h"

HealthBar::HealthBar(Healthy* parent, float scale) : Object("../assets/healthbar.png") {
	this->parent = parent;

    mass = 0;
    kinematic = true;
    background = true;
    transparent = true;
    Scale(scale);
}

bool HealthBar::Update() {
    if (parent->gonnaBeDeleted)
        return true;
	MoveTo(parent->GetPos() + Vector2(0, -parent->GetH() / 2 - 20 - GetH() / 2));
	image.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(IMG_SIZE.x / parent->MaxHP() * parent->HP(), IMG_SIZE.y)
    ));
    return false;
}

Vector2 HealthBar::IMG_SIZE = Vector2(100, 20);