#include "Vadid.h"
#include "Player.h"
#include "Overlay.h"
#include <foresteamnd/Utils.h>

Vadid::Vadid(float kDamage) : Healthy(150, "../assets/textures/boss.png", RECT_SIZE) {
    this->kDamage = kDamage;
    this->mass = 1;
	direction = 1;
    Scale(Vector2(.3f));
    touchAttack = new MeleeAttack(GetW() * 1.05f, GetH() * .05f, 50, 0, 0.5f, 0);
    spikeAttack = new SpikeAttack(100, 50, .4f, 0, .7f);
    lastChoice = Choise();
    choiseTimer = clock();
    attacked = false;

    wave = nullptr;
    title = new Overlay(Vector2(window_width / 2, window_height / 2), "../assets/textures/boss_title.png");

	InitHealthBar();
	SetState(IDLE);
}
Vadid::~Vadid() {
    delete touchAttack;
    delete spikeAttack;
}

void Vadid::SetState(STATE state) {
	image.setTextureRect(sf::IntRect(sf::Vector2i(RECT_SIZE.x * state, 0), v2i(RECT_SIZE)));
}
void Vadid::TakeDamage(float amount, Object* source) {
	Healthy::TakeDamage(amount, source);
    if (instanceof<Player>(source))
        if (!Alive())
            aSwordExecuteSound.Play();
        else
            aSwordSliceSound.Play();
}

bool Vadid::Update(list<Object*>& objects) {
	Player* ply = nullptr;
	for (Object* o : objects)
		if (instanceof <Player>(o)) {
			ply = (Player*)o;
			break;
		}

	if (!lastChoice.attack)
		if (onGround)
			SetState(IDLE);
		else
			SetState(JUMP_ATTACK);

	if (ply) {
		direction = (ply->GetPos().x > GetPos().x) * 2 - 1;
        if (touchAttack->Ready() && touchAttack->GetZone(this, 0).intersects(ply->image.getGlobalBounds())) {
            touchAttack->DoAttack(this, 0, objects);
        }
        if (float(clock() - choiseTimer) / CLOCKS_PER_SEC > choiseInterval) {
            if (title) {
                delete title;
                title = nullptr;
            }
            if (!lastChoice.attack) {
                Choise t[] = { Choise(spikeAttack, ATTACK, ATTACK) };
                lastChoice = t[(int)Utils::RandRange(0, 1)];
                lastChoice.attack->Prepare();
                SetState(lastChoice.stateCharge);
                if (instanceof<SpikeAttack>(lastChoice.attack)) {
                    velocity.y += -mass * 0.4 * GetScale().Length();
					wave = new Overlay(Vector2(window_width / 2, window_height - 100 / 2) , "../assets/textures/flame.png");
					wave->enabled = false;
                }
            }
            if (attacked) {
                if (lastChoice.attack->Ready()) {
                    lastChoice = Choise();
                    choiseTimer = clock();
                    attacked = false;
                    if (wave) {
                        delete wave;
                        wave = nullptr;
                    }
                }
            }
            else
                if (lastChoice.attack->Prepared()) {
                    lastChoice.attack->DoAttack(this, 0, objects);
                    SetState(lastChoice.stateAttack);
                    attacked = true;
                    if (wave)
                        wave->enabled = true;
                }
        }
	}

	return Healthy::Update(objects);
}
void Vadid::Draw(sf::RenderWindow& window) {
    Healthy::Draw(window);
    if (wave)
        wave->Draw(window);
    if (title)
        title->Draw(window);
}

Vector2 Vadid::RECT_SIZE = Vector2(253, 262);