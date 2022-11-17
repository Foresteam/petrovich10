#include "Overlay.h"

Overlay::Overlay(Vector2 pos, std::string filename, Vector2 rectSize) : Entity(filename, rectSize) {
	mass = 0;
	kinematic = true;
	transparent = true;
	background = true;
    MoveTo(pos);
}