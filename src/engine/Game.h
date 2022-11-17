#pragma once
#include "../Dragger.h"
#include "../entities/Entity.h"
#include "../entities/Overlay.h"
#include "../entities/Player.h"
#include "../gui/GUIElement.h"
// #include "../entities/Vadid.h"
#include "Level.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <list>
#include <vector>

class Game {
private:
	Player* me;
	Overlay* gameOver;
	list<Entity*> objects;
	Dragger dragger;

	std::list<Level*> _levels;
	double renderWait = 0;
	// this clock is the fix for tremendous GPU utilizing. Alongside with FPS limiting, ofc
	chrono::_V2::steady_clock::time_point lastUpdate = chrono::steady_clock::now();

	void FitInScreen(Entity* object);
	void DeltaTime();
	bool RenderWait();
	void HandleGlobalSounds();
	void GameCycle(sf::RenderWindow& window, bool &exit);
	void MainMenu(sf::RenderWindow& window, bool& exit);

	void FindMe();
public:
	vector<GUIElement*> mainMenu;
	~Game();

	void LifeCycle(sf::RenderWindow& window);
	void AddLevel(Level* level);
};