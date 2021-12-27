#pragma once
#include "Healthy.h"
#include "../MeleeAttacker.h"
#include "../global.h"
#include <time.h>
#include <list>

class Player : public Healthy, private MeleeAttacker {
private:
    static Vector2 IMG_SIZE;
    const float K_SPEED = 1e-1 * 6;
    const float JUMP_POWER = .16;

    int direction;
    void SetState(STATE state) override;
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