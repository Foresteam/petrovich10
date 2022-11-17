#include "Level.h"

Level::Level(LevelGenFunction generator, bool shouldCleanup) {
	_generator = generator;
	_shouldCleanup = shouldCleanup;
}
void Level::Generate(std::list<Entity*>& entities) {
	_generator(entities);
}
bool Level::ShouldCleanup() {
	return _shouldCleanup;
}