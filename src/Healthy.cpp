#include "Healthy.h"

Healthy::Healthy(std::string file, Vector2 imgsz, float maxHP) : Object(file, imgsz) {
	this->maxHP = maxHP;
	hp = maxHP;
}
Healthy::Healthy(std::string file, float maxHP) : Healthy(file, Vector2(), maxHP) {}
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