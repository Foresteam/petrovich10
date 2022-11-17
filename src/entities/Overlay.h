#pragma once
#include "Entity.h"

class Overlay : public Entity {
public:
    Overlay(Vector2 pos, std::string filename, Vector2 rectSize = Vector2());
};