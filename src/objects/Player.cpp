#include "Player.h"

Player::Player(bool isMe) : Healthy("../assets/player.png", IMG_SIZE, 100) {
	this->isMe = isMe;

	direction = -1;
	mass = 1;
	Scale(Vector2(.7f));
	SetState(STATE::IDLE);
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
	
	if (AttackReset() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		Attack(objects);
}

float Player::KSpeed() {
	return K_SPEED * GetScale().Length();
}
float Player::JumpPower() {
	return JUMP_POWER * GetScale().Length();
}

bool Player::AttackReset() {
	if (lastSwing == 0)
		return true;
	if (float(clock() - lastSwing) / CLOCKS_PER_SEC < ATTACK_COOLDOWN)
		return false;
	lastSwing = 0;
	SetState(STATE::IDLE);
	return true;
}
void Player::Attack(list<Object*>& objects) {
	lastSwing = clock();
	SetState(STATE::ATTACK);
	sf::FloatRect zone = sf::FloatRect(sf::Vector2f(GetPos().x, GetPos().y - GetH() / 2), sf::Vector2f(100 * direction, GetH()));

	for (Object* o : objects)
		if (o != this && sf::FloatRect(v2f(o->GetPos() - (o->GetSize() / 2)), v2f(o->GetSize())).intersects(zone))
			o->TakeDamage(10);
}

void Player::TakeDamage(float amount) {
	SetHP(HP() - amount);
}
bool Player::Update() {
	return !Alive() && (gonnaBeDeleted = true);
}

Vector2 Player::IMG_SIZE = Vector2(180, 199);