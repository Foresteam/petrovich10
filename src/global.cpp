#include "global.h"

float deltaTime = 0;

Vector2 f2v(const sf::Vector2f& vec) {
    return Vector2(vec.x, vec.y);
}
sf::Vector2f v2f(const Vector2& vec) {
    return sf::Vector2f(vec.x, vec.y);
}
Vector2 i2v(const sf::Vector2i& vec) {
    return Vector2(vec.x, vec.y);
}
sf::Vector2i v2i(const Vector2& vec) {
    return sf::Vector2i(vec.x, vec.y);
}

RandomSound aSwordSwingSound = RandomSound("../assets/sounds/swing", ".ogg", 5);
RandomSound aSwordSliceSound = RandomSound("../assets/sounds/slice", ".ogg", 6);
RandomSound aSwordExecuteSound = RandomSound("../assets/sounds/sword_execute", ".ogg", 9);

sf::SoundBuffer wallBreakBuffer;
sf::Sound wallBreakSound;