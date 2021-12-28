#pragma once
#include "Object.h"

class Overlay : public Object {
public:
    Overlay(Vector2 pos, std::string filename, Vector2 rectSize = Vector2());
};