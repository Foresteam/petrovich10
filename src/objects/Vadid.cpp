#include "Vadid.h"
#include "Player.h"
#include "Overlay.h"
#include <foresteamnd/Utils.h>

Vadid::Vadid(float kDamage) : Healthy(150, ASSETS + "textures/boss.png", RECT_SIZE) {
    this->kDamage = kDamage;
    this->mass = 1;
	direction = 1;
    Scale(Vector2(.3f));
    touchAttack = new MeleeAttack(GetW(), 0, 50, 0, 0.5f, 0);
    spikeAttack = new SpikeAttack(100, 100, .4f, 0, .7f);
    jumpAttack = new Attack(0, 0, 0, .5);
    lastChoice = Choise();
    choiseTimer = clock();
    attacked = false;

    wave = nullptr;
    title = new Overlay(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), ASSETS + "textures/boss_title.png");

    rasenganBuffer.loadFromFile(ASSETS + "sounds/rassengan.ogg");
    rasenganSound.setBuffer(rasenganBuffer);

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
		if (!ply || onGround) // wtf?
			SetState(IDLE);
		else
			SetState(JUMP_ATTACK);

    Rotate(direction, false);
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
                Choise t[] = { Choise(spikeAttack, ATTACK, ATTACK), Choise(jumpAttack, JUMP_ATTACK, JUMP_PREPARE) };
                lastChoice = t[(int)Utils::RandRange(0, 2)];
                lastChoice.attack->Prepare();
                SetState(lastChoice.stateCharge);
                if (instanceof<SpikeAttack>(lastChoice.attack)) {
                    velocity.y += -mass * 0.4 * GetScale().Length();
					wave = new Overlay(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100 / 2) , ASSETS + "textures/flame.png");
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
                    if (instanceof<SpikeAttack>(lastChoice.attack))
                        rasenganSound.play();
                    else {
						velocity += Vector2(
							((ply->GetPos().x < GetPos().x) * 2 - 1) * -0.5 * ply->GetPos().Distance(GetPos()) * 1e+1,
							-.2f * mass * GetScale().Length() + (1 - (GetPos().y / ply->GetPos().y)) / 8
                        );
					}
                }
        }
	}

    bool dead = Healthy::Update(objects);
    if (dead) {
        Overlay* victory = new Overlay(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), ASSETS + "textures/victory.png");
        objects.push_back(victory);
    }

	return dead;
}
void Vadid::Draw(sf::RenderWindow& window) {
    Healthy::Draw(window);
    if (wave)
        wave->Draw(window);
    if (title)
        title->Draw(window);
}

Vector2 Vadid::RECT_SIZE = Vector2(253, 262);