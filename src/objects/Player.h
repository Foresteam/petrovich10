#pragma once
#include "Healthy.h"
#include "../MeleeAttack.h"
#include "../global.h"
#include "../RandomSound.h"
#include <time.h>
#include <list>

class Player : public Healthy {
private:
    enum STATE { IDLE = 0, ATTACK };

    static Vector2 IMG_SIZE;
    const float K_SPEED = 1e-1 * 6;
    const float JUMP_POWER = .221f;

    int direction;
    MeleeAttack* attack;
    void SetState(STATE state);
public:
	/// Is local player
	bool isMe;

    /// @param isMe Is local player
    Player(bool isMe = false);
    ~Player();

	void Control(sf::RenderWindow& window, list<Object*>& objects);

	float JumpPower();
    float KSpeed();

    void TakeDamage(float amount) override;
	bool Update(list<Object*>& objects) override;
};