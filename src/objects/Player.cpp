#include "Player.h"
#include "HealthBar.h"
#include "../global.h"

Player::Player(bool isMe) : Healthy(100, "../assets/textures/player.png", RECT_SIZE) {
	this->isMe = isMe;

	direction = -1;
	mass = 1;
	Scale(Vector2(.7f));
	SetState(STATE::IDLE);
	InitHealthBar();

	attack = new MeleeAttack(GetW() / 2 + 70, 0, 10, .2f, .3f);
}
Player::~Player() {
	delete attack;
}

void Player::SetState(STATE state) {
	image.setTextureRect(sf::IntRect(sf::Vector2i(RECT_SIZE.x * state, 0), v2i(RECT_SIZE)));
}

void Player::Control(sf::RenderWindow& window, list<Object*>& objects) {
	int plyMove = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
	direction = plyMove ? plyMove : direction;
	
	Rotate(direction, false);

	velocity.x = plyMove * KSpeed() * (!onGround + 1);
	// Move(Vector2(velocity.x, 0));

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

void Player::TakeDamage(float amount, Object* source) {
	Healthy::TakeDamage(amount, source);
	if (!Alive())
		aSwordExecuteSound.Play();
	else
		aSwordSliceSound.Play();
}

Vector2 Player::RECT_SIZE = Vector2(180, 199);