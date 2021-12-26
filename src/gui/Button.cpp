#include "Button.h"

Button::Button(Vector2 pos, string filename, Vector2 textureRectSize) : GUIElement(pos, filename, textureRectSize) {
    clickable = true;
}