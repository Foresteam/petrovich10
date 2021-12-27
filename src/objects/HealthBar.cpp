#include "HealthBar.h"

HealthBar::~HealthBar() {
    delete _background;
}
HealthBar::HealthBar(Healthy* parent, float scale) : Object("../assets/textures/healthbar.png") {
	this->parent = parent;

    _background = new Object("../assets/textures/healthbar_background.png");
    _background->mass = 0;
    _background->background = true;
    _background->transparent = true;
    _background->kinematic = true;
    _background->Scale(scale);

    mass = 0;
    kinematic = true;
    background = true;
    transparent = true;
    Scale(scale);
}

bool HealthBar::Update() {
	MoveTo(parent->GetPos() + Vector2(0, -parent->GetH() / 2 - 20 - GetH() / 2));
	_background->MoveTo(GetPos());
	image.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(IMG_SIZE.x / parent->MaxHP() * parent->HP(), IMG_SIZE.y)
    ));
    return false;
}
void HealthBar::Draw(sf::RenderWindow& window) {
    Object::Draw(window);
    _background->Draw(window);
}

Vector2 HealthBar::IMG_SIZE = Vector2(100, 20);