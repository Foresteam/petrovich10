#pragma once
#include "GUIElement.h"

class Button : public GUIElement {
public:
	Button(Vector2 pos, string filename, Vector2 textureRectSize = Vector2());
};