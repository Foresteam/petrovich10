#pragma once
#include "Healthy.h"
#include "../attacks/SpikeAttack.h"
#include "../attacks/MeleeAttack.h"

class Vadid : public Healthy {
private:
	static Vector2 RECT_SIZE;
	enum STATE { IDLE = 0, ATTACK = 3, JUMP_ATTACK };

    struct Choise {
        Attack* attack;
        STATE stateAttack, stateCharge;
        Choise() {
            attack = nullptr;
            stateAttack = IDLE;
			stateCharge = IDLE;
		}
		Choise(Attack* attack, STATE stateAttack, STATE stateCharge) {
			this->attack = attack;
            this->stateAttack = stateAttack;
			this->stateCharge = stateCharge;
		}
	};

	int direction;
    float kDamage;
	MeleeAttack* touchAttack;
    SpikeAttack* spikeAttack;

    const float choiseInterval = 5;
    float choiseTimer;
    Choise lastChoice;
    bool attacked;

    Object* wave;
	Object* title;
public:
	Vadid(float kDamage);
	~Vadid();
	void TakeDamage(float amount, Object* source) override;
	bool Update(list<Object*>& objects) override;
    void Draw(sf::RenderWindow& window) override;
	void SetState(STATE state);
};