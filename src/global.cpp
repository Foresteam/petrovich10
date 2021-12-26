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