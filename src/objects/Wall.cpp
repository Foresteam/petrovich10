#include "Wall.h"

Wall::Wall() : Object("../assets/wall.png") {
    mass = 500;
    // kinematic = true;
    Scale(Vector2(.6f));
}