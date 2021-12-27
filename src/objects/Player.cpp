#include "Player.h"
#include "HealthBar.h"
#include "../global.h"

Player::Player(bool isMe) : Healthy(100, "../assets/textures/player.png", IMG_SIZE) {
	this->isMe = isMe;

	attack = new MeleeAttack(100, 0, 10, .2f, .3f);
	direction = -1;
	mass = 1;
	Scale(Vector2(.7f));
	SetState(STATE::IDLE);
	InitHealthBar();
}
Player::~Player() {
	delete attack;
}

void Player::SetState(STATE state) {
	image.setTextureRect(sf::IntRect(sf::Vector2i(IMG_SIZE.x * state, 0), v2i(IMG_SIZE)));
}

void Player::Control(sf::RenderWindow& window, list<Object*>& objects) {
	int plyMove = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
	direction = plyMove ? plyMove : direction;
	auto scale = image.getScale();
	if (plyMove < 0 && scale.x < 0)
		image.setScale(-scale.x, scale.y);
	else if (plyMove > 0 && scale.x > 0)
		image.setScale(-scale.x, scale.y);
	velocity.x = plyMove * deltaTime * KSpeed();
	Move(Vector2(velocity.x, 0));

	if (onGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) // velocity.y == 0
		velocity.y -= JumpPower();
	
	if (attack->Reset()) {
		SetState(IDLE);
		if (attack->Ready() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
			attack->DoAttack(this, direction, objects);
			SetState(ATTACK);
			aSwordSwingSound.Play();
		}
	}
}

float Player::KSpeed() {
	return K_SPEED * GetScale().Length();
}
float Player::JumpPower() {
	return JUMP_POWER * GetScale().Length() * mass;
}

bool Player::Update(list<Object*>& objects) {
	Healthy::Update(objects);
	return !Alive();
}

void Player::TakeDamage(float amount) {
	Healthy::TakeDamage(amount);
	if (!Alive())
		aSwordExecuteSound.Play();
	else
		aSwordSliceSound.Play();
}

Vector2 Player::IMG_SIZE = Vector2(180, 199);