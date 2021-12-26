#pragma once
#include "../objects/Object.h"

class GUIElement : public Object {
public:
	bool clickable;
	GUIElement(Vector2 pos, string filename, Vector2 textureRectSize = Vector2());
	bool TestClick(Vector2 pos);
};