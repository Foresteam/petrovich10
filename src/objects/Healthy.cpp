#include "Healthy.h"

Healthy::Healthy(float maxHP, string file, Vector2 imgsz) : Object(file, imgsz) {
	this->maxHP = maxHP;
	hp = maxHP;
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