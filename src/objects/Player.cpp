#include "Player.h"
#include "HealthBar.h"

Player::Player(bool isMe) : Healthy(100, "../assets/player.png", IMG_SIZE), MeleeAttacker(100) {
	this->isMe = isMe;

	direction = -1;
	mass = 1;
	Scale(Vector2(.7f));
	SetState(STATE::IDLE);
	InitHealthBar();
}

void Player::SetState(STATE state) {
	image.setTextureRect(sf::IntRect(sf::Vector2i(IMG_SIZE.x * state, 0), v2i(IMG_SIZE)));
}

void Player::Control(sf::RenderWindow& window, list<Object*>& objects) {
	int plyMove = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
	direction = plyMove ? plyMove : direction;
	auto scale = this->image.getScale();
	if (plyMove < 0 && scale.x < 0)
		this->image.setScale(-scale.x, scale.y);
	else if (plyMove > 0 && scale.x > 0)
		this->image.setScale(-scale.x, scale.y);
	this->velocity.x = plyMove * deltaTime * KSpeed();
	this->Move(Vector2(velocity.x, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->velocity.y == 0)
		this->velocity.y -= JumpPower();
	
	if (AttackReset()) {
		SetState(IDLE);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
			Attack(this, direction, objects);
			SetState(ATTACK);
		}
	}
}

float Player::KSpeed() {
	return K_SPEED * GetScale().Length();
}
float Player::JumpPower() {
	return JUMP_POWER * GetScale().Length();
}

void Player::TakeDamage(float amount) {
	SetHP(HP() - amount);
}
bool Player::Update() {
	Healthy::Update();
	return !Alive();
}

Vector2 Player::IMG_SIZE = Vector2(180, 199);