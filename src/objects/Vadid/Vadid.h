#pragma once
#include "../Healthy.h"
#include "../../attacks/SpikeAttack.h"
#include "../../attacks/MeleeAttack.h"
#include "Rasengan.h"
#include <list>

class Vadid : public Healthy {
private:
	enum STATE { IDLE = 0, AWAKEN = 1, JUMP_PREPARE = 2, ATTACK = 3, JUMP_ATTACK };

	struct Choise {
		Attack* attack;
		STATE stateAttack, stateCharge;
		Choise(Attack* attack, STATE stateAttack, STATE stateCharge) {
			this->attack = attack;
			this->stateAttack = stateAttack;
			this->stateCharge = stateCharge;
		}
		Choise(Attack* attack) : Choise(attack, IDLE, IDLE) {}
		Choise() : Choise(nullptr) {}
	};

	int _direction;
	float _kDamage;
	MeleeAttack* _touchAttack;
	SpikeAttack* _spikeAttack;
	Attack* _jumpAttack;
	Attack* _rasenganAttack;
	STATE _state;

	const float choiseInterval = 2;
	float _choiseTimer;
	Choise _lastChoice;
	bool _attacked;

	Object* _wave;
	Object* _title;

	const int afterimagesMaxSkipFrames = 2;
	const int afterimagesMax = 5;
	list<Object*> _afterimages;
	int _afterimageSkippedFrames;

	sf::SoundBuffer _rasenganBuffer, _rasenganShotBuffer;
	sf::Sound _rasenganSound, _rasenganShotSound;
public:
	static Vector2 RECT_SIZE, SCALE;
	Vadid(float kDamage);
	~Vadid();
	void TakeDamage(float amount, Object* source) override;
	bool Update(list<Object*>& objects) override;
	void Draw(sf::RenderWindow& window) override;
	void SetState(STATE state);
	int GetPhase();
};