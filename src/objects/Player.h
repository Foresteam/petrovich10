#pragma once
#include "Object.h"
#include "Healthy.h"
#include "../global.h"
#include <time.h>
#include <list>

class Player : public Healthy {
private:
    static Vector2 IMG_SIZE;
    const float K_SPEED = 1e-1 * 6;
    const float JUMP_POWER = .16;
    const float ATTACK_COOLDOWN = .3f;
    const float AP = 10;
    enum STATE { IDLE = 0, ATTACK };

    void SetState(STATE state);

    int direction;

    clock_t lastSwing = 0;
    void Attack(list<Object*>& objects);
    bool AttackReset();
public:
	/// Is local player
	bool isMe;

    /// @param isMe Is local player
    Player(bool isMe = false);

	void Control(sf::RenderWindow& window, list<Object*>& objects);

	float JumpPower();
    float KSpeed();

    void TakeDamage(float amount) override;
    bool Update() override;
};