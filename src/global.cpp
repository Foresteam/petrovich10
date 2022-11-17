#include "global.h"
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <foresteamnd/ExePath>

double deltaTime = 0;

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

std::string DefaultToLocal(std::string path) {
	return path.length() > 1 ? path : "./";
}

std::string EXE_PATH = DefaultToLocal(ExePath::getExecutableDir());

RandomSound aSwordSwingSound = RandomSound(ASSETS + "sounds/swing", ".ogg", 5);
RandomSound aSwordSliceSound = RandomSound(ASSETS + "sounds/slice", ".ogg", 6);
RandomSound aSwordExecuteSound = RandomSound(ASSETS + "sounds/sword_execute", ".ogg", 9);
RandomSound aPunchSound = RandomSound(ASSETS + "sounds/punch", ".ogg", 6);
RandomSound anAirWaveSound = RandomSound(ASSETS + "sounds/air_wave", ".ogg", 2);

sf::SoundBuffer wallBreakBuffer;
sf::Sound wallBreakSound;

std::list<Sound**> globalSounds;

float CalcJumpPower(Vector2 scale, float mass, float boost) {
	return BASE_JUMP_POWER * scale.Length() * mass * boost;
}