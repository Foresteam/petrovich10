#include "HealthBar.h"

HealthBar::~HealthBar() {
    delete _background;
}
HealthBar::HealthBar(Healthy* parent, float scale) : Overlay(Vector2(), ASSETS + "textures/healthbar.png") {
	this->parent = parent;

    _background = new Object(ASSETS + "textures/healthbar_background.png");
    _background->mass = 0;
    _background->background = true;
    _background->transparent = true;
    _background->kinematic = true;
    _background->Scale(scale);

    Scale(scale);
}

bool HealthBar::Update(list<Object*>& objects) {
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