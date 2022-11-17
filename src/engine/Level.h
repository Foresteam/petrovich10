#pragma once
#include "../entities/Entity.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <list>

typedef std::function<void(std::list<Entity*>&)> LevelGenFunction;

class Level {
private:
	bool _shouldCleanup;
	LevelGenFunction _generator;
public:
	Level(LevelGenFunction generator, bool shouldCleanup = false);
	void Generate(std::list<Entity*>& entities);
	bool ShouldCleanup();
};