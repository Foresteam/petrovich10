#include "Enemy.h"
#include "Player.h"
#include "../global.h"

const float attackRange = 300;

Enemy::Enemy() : Healthy(100, "../assets/textures/enemy2.png", IMG_SIZE), MeleeAttacker(attackRange, 70, 50, .5f, 1, .7f) {
    mass = .5;
    Scale(Vector2(0.3f));
	InitHealthBar();
    isSeeingPlayer = false;
    direction = 1;
    SetState(IDLE);
}

void Enemy::TakeDamage(float amount) {
    Healthy::TakeDamage(amount);
    if (!Alive())
        aSwordExecuteSound.Play();
    else
        aSwordSliceSound.Play();
}
void Enemy::SetState(STATE state) {
	image.setTextureRect(sf::IntRect(sf::Vector2i(IMG_SIZE.x * state, 0), v2i(IMG_SIZE)));
}

bool Enemy::Update(list<Object*>& objects) {

	Player* ply = nullptr;
    for (Object* o : objects)
        if (instanceof<Player>(o)) {
            ply = (Player*)o;
            break;
        }
    if (AttackReset())
        SetState(IDLE);
    bool inRange = false;
    if (ply) {
        direction = (ply->GetPos().x > GetPos().x) * 2 - 1;
		inRange = GetZone(this, direction).intersects(ply->image.getGlobalBounds());
        if (inRange) {
            if (!isSeeingPlayer) {
                AttackPrepare();
                isSeeingPlayer = true;
            }
            if (AttackReset() && AttackReady() && AttackPrepared()) {
                Attack(this, direction, objects);
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

Vector2 Enemy::IMG_SIZE = Vector2(1898 / 2, 707);