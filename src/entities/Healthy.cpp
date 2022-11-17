#include "Healthy.h"
#include "HealthBar.h"

Healthy::Healthy(float maxHP, string file, Vector2 imgsz) : Entity(file, imgsz) {
	this->maxHP = maxHP;
	hp = maxHP;
	healthBar = nullptr;
}
Healthy::~Healthy() {
	if (healthBar)
		delete healthBar;
}
float Healthy::HP() {
	return hp;
}
float Healthy::MaxHP() {
	return maxHP;
}
void Healthy::SetHP(float val) {
	hp = val;
    if (hp < 0)
        hp = 0;
}
bool Healthy::Alive() {
	return hp > 0;
}
void Healthy::Draw(sf::RenderWindow& window) {
	Entity::Draw(window);
	if (healthBar)
		healthBar->Draw(window);
}
void Healthy::InitHealthBar() {
	healthBar = new HealthBar(this, GetW() / 100 / 2);
}
bool Healthy::Update(list<Entity*>& objects) {
	if (healthBar)
		healthBar->Update(objects);
	Entity::Update(objects);
	return !Alive();
}
void Healthy::TakeDamage(float amount, Entity* source) {
	SetHP(HP() - amount);
}