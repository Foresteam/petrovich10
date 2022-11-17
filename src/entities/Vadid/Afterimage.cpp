#include "Afterimage.h"
#include "Vadid.h"

Afterimage::Afterimage(Vector2 pos) : Entity(ASSETS + "textures/boss_afterimage.png", Vadid::RECT_SIZE) {
	kinematic = true;
	transparent = true;
	MoveTo(pos);
	Scale(Vadid::SCALE);
}