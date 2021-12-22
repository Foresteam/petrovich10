#include "HealthBar.h"

HealthBar::HealthBar(Healthy* hparent, Object* oparent, float scale) : Object("../assets/healthbar.png") {
	this->hparent = hparent;
    this->oparent = oparent;

    mass = 0;
    kinematic = true;
    background = true;
    Scale(scale);
}

bool HealthBar::Update() {
    if (oparent->gonnaBeDeleted)
        return true;
	MoveTo(oparent->GetPos() + Vector2(0, -oparent->GetH() / 2 - 20 - GetH() / 2));
	image.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(IMG_SIZE.x / hparent->MaxHP() * hparent->HP(), IMG_SIZE.y)
    ));
    return false;
}

Vector2 HealthBar::IMG_SIZE = Vector2(100, 20);