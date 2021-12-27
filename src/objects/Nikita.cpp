#include "Nikita.h"
#include "Player.h"
#include "../global.h"

const float attackRange = 300;

Nikita::Nikita() : Healthy(100, "../assets/textures/enemy2.png", IMG_SIZE) {
    mass = .5;
    Scale(Vector2(0.3f));
	InitHealthBar();
    isSeeingPlayer = false;
    direction = 1;
    attack = new MeleeAttack(attackRange, 70, 50, .5f, 1, .7f);
    SetState(IDLE);
}
Nikita::~Nikita() {
    delete attack;
}

void Nikita::TakeDamage(float amount) {
    Healthy::TakeDamage(amount);
    if (!Alive())
        aSwordExecuteSound.Play();
    else
        aSwordSliceSound.Play();
}
void Nikita::SetState(STATE state) {
	image.setTextureRect(sf::IntRect(sf::Vector2i(IMG_SIZE.x * state, 0), v2i(IMG_SIZE)));
}

bool Nikita::Update(list<Object*>& objects) {

	Player* ply = nullptr;
    for (Object* o : objects)
        if (instanceof<Player>(o)) {
            ply = (Player*)o;
            break;
        }
    if (attack->Reset())
        SetState(IDLE);
    bool inRange = false;
    if (ply) {
        direction = (ply->GetPos().x > GetPos().x) * 2 - 1;
		inRange = attack->GetZone(this, direction).intersects(ply->image.getGlobalBounds());
        if (inRange) {
            if (!isSeeingPlayer) {
                attack->Prepare();
                isSeeingPlayer = true;
            }
            if (attack->Reset() && attack->Ready() && attack->Prepared()) {
                attack->DoAttack(this, direction, objects);
                SetState(ATTACK);
                aSwordSwingSound.Play();
            }
        }
    }
    if (!ply || !inRange)
        isSeeingPlayer = false;

	auto scale = image.getScale();
	if (direction > 0 && scale.x < 0)
		image.setScale(-scale.x, scale.y);
	else if (direction < 0 && scale.x > 0)
		image.setScale(-scale.x, scale.y);

	Healthy::Update(objects);
    return !Alive();
}

Vector2 Nikita::IMG_SIZE = Vector2(1898 / 2, 707);