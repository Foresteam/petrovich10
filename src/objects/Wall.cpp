#include "Wall.h"

Wall::Wall() : Object("../assets/wall.png") {
    mass = 100;
    // kinematic = true;
    Scale(Vector2(.6f));
}