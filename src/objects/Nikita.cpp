#include "Nikita.h"
#include "Player.h"
#include "Wall.h"
#include "Vadid.h"
#include "../global.h"

const float attackRange = 300;

Nikita::Nikita() : Healthy(100, "../assets/textures/enemy2.png", RECT_SIZE) {
    mass = .5;
    Scale(Vector2(0.3f));
	InitHealthBar();
    isSeeingPlayer = false;
    direction = 1;
    attack = new MeleeAttack(attackRange, 70, 50, .5f, 1, .5f);
    SetState(IDLE);
}
Nikita::~Nikita() {
    delete attack;
}

void Nikita::TakeDamage(float amount, Object* source) {
	Healthy::TakeDamage(amount, source);
    if (!Alive())
        aSwordExecuteSound.Play();
    else
        aSwordSliceSound.Play();
}
void Nikita::SetState(STATE state) {
	image.setTextureRect(sf::IntRect(sf::Vector2i(RECT_SIZE.x * state, 0), v2i(RECT_SIZE)));
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

	Rotate(direction, true);

    bool dead = Healthy::Update(objects);
    if (dead) {
		Vadid* vadid;
        Wall* wall;
        vadid = new Vadid(1);
		vadid->MoveTo(Vector2(WINDOW_WIDTH / 2, 0));
		objects.push_back(vadid);

        wall = new Wall();
        wall->MoveTo(Vector2(200, 0));
        objects.push_back(wall);

		wall = new Wall();
		wall->MoveTo(Vector2(WINDOW_WIDTH - 200, 0));
		objects.push_back(wall);
	}
    return dead;
}

Vector2 Nikita::RECT_SIZE = Vector2(1898 / 2, 707);