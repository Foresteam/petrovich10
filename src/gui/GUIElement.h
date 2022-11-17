#pragma once
#include "../entities/Entity.h"

class GUIElement : public Entity {
public:
	bool clickable;
	GUIElement(Vector2 pos, string filename, Vector2 textureRectSize = Vector2());
	bool TestClick(Vector2 pos);
};