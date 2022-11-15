#pragma once
#include "Healthy.h"
#include "../attacks/MeleeAttack.h"
#include "../global.h"
#include "../RandomSound.h"
#include <time.h>
#include <list>

class Player : public Healthy {
private:
	enum STATE { IDLE = 0, ATTACK };

	static Vector2 RECT_SIZE;
	const float K_SPEED = 1e+2 * 6;
	const float JUMP_POWER = G * G_SCALE / 4;

	int direction;
	MeleeAttack* attack;
	void SetState(STATE state);

	/// Is local player
	bool _isMe;
public:
	bool IsMe();

	/// @param isMe Is local player
	Player(bool isMe = false);
	~Player();

	void Control(sf::RenderWindow& window, list<Object*>& objects);

	float JumpPower();
	float KSpeed();

	void TakeDamage(float amount, Object* source) override;
	bool Update(list<Object*>& objects) override;
};