#include "Healthy.h"
#include "HealthBar.h"

Healthy::Healthy(float maxHP, string file, Vector2 imgsz) : Object(file, imgsz) {
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
	Object::Draw(window);
	if (healthBar)
		healthBar->Draw(window);
}
void Healthy::InitHealthBar() {
	healthBar = new HealthBar(this, (abs(this->GetScale().x) + abs(this->GetScale().y)) / 2);
}
bool Healthy::Update(list<Object*>& objects) {
	if (healthBar)
		healthBar->Update(objects);
	return !Alive();
}
void Healthy::TakeDamage(float amount) {
	SetHP(HP() - amount);
}