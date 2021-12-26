#include "GUIElement.h"

GUIElement::GUIElement(Vector2 pos, string filename, Vector2 textureRectSize) : Object(filename, textureRectSize) {
    MoveTo(pos);
    clickable = false;
}

bool GUIElement::TestClick(Vector2 pos) {
	return clickable && hitbox.GetRect().contains(v2f(pos));
}