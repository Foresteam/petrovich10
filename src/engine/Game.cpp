#include "Game.h"
#include <thread>
#include <unistd.h>
using namespace chrono;

void Game::FitInScreen(Entity* object) {
	if (object->GetPos().x < 0 + object->GetW() / 2 && object->CanCollide(nullptr, Vector2(1, 0))) {
		object->MoveTo(Vector2(0 + object->GetW() / 2, object->GetPos().y));
		object->velocity.x = 0;
	}
	if (object->GetPos().x > WINDOW_WIDTH - object->GetW() / 2 && object->CanCollide(nullptr, Vector2(-1, 0))) {
		object->MoveTo(Vector2(WINDOW_WIDTH - object->GetW() / 2, object->GetPos().y));
		object->velocity.x = 0;
	}
	if (object->GetPos().y < 0 + object->GetH() / 2 && object->CanCollide(nullptr, Vector2(0, 1))) {
		object->MoveTo(Vector2(object->GetPos().x, 0 + object->GetH() / 2));
		object->velocity.y = 0;
	}
	if (object->GetPos().y >= WINDOW_HEIGHT - object->GetH() / 2)
		object->onGround = true;
	if (object->GetPos().y > WINDOW_HEIGHT - object->GetH() / 2 && object->CanCollide(nullptr, Vector2(0, -1))) {
		object->MoveTo(Vector2(object->GetPos().x, WINDOW_HEIGHT - object->GetH() / 2));
		object->velocity.y = 0;
	}
}
void Game::DeltaTime() {
	auto now = steady_clock::now();
	deltaTime = duration_cast<duration<double>>(now - lastUpdate).count();
	lastUpdate = now;
}
bool Game::RenderWait() {
	if (renderWait > 1.f / FPS) {
		renderWait = 0;
		return true;
	} else {
		renderWait += deltaTime;
		return false;
	}
}

void Game::HandleGlobalSounds() {
	list<Sound**> dead;
	for (auto& sound : globalSounds) {
		(*sound)->Update();
		if ((*sound)->GetStatus() == Sound::STATUS::NOT_PLAYING)
			dead.push_back(sound);
	}
	// purge
	for (auto& sound : dead) {
		globalSounds.remove(sound);
		delete *sound;
		*sound = nullptr;
	}
}

void Game::GameCycle(sf::RenderWindow& window, bool& exit) {
	DeltaTime();
	map<Entity*, Entity*> checkedCollision;
	list<Entity*> toDelete;
	while (window.isOpen()) {
		sf::Event event;

		if (me) {
			me->Control(window, objects);
			dragger.DoDrag(window);
		} else
			gameOver->enabled = true;

		checkedCollision.clear();
		toDelete.clear();
		for (Entity* object : objects) {
			if (object->Update(objects))
				toDelete.push_back(object);
			object->onGround = false; // <= the reason
		}
		// two cycles go through the same array. Nice.
		for (Entity* object : objects) {
			object->Gravitate();
			for (Entity* object2 : objects)
				if (object != object2 && (checkedCollision[object] != object2) && (checkedCollision[object2] != object)) {
					object->Collide(*object2);
					checkedCollision.insert_or_assign(object, object2);
				}
			FitInScreen(object);
		}

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
					dragger.TryCapture(objects, event);
				break;
			case sf::Event::MouseButtonReleased:
				dragger.Release();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Key::Escape)
					return;
				break;
			case sf::Event::Closed:
				exit = true;
				return;
			}
		}

		DeltaTime();

		// draw the objects
		if (RenderWait()) {
			window.clear();
			for (Entity* o : objects)
				o->Draw(window);
			window.display();
		}

		HandleGlobalSounds();
		for (Entity* o : toDelete) {
			if (o == me) {
				me = nullptr;
				dragger.Release();
			}
			delete o;
			objects.remove(o);
		}
	}
}

void Game::MainMenu(sf::RenderWindow& window, bool& exit) {
	while (window.isOpen()) {
		DeltaTime();
		// here we limit, mostly, CPU performance, to not make it calculate the nothing that happens
		// we can do this 'cuz then we use pollEvent, that "stacks" the incoming events, 'til take pull 'em out
		if (RenderWait())
			this_thread::sleep_for(milliseconds(100));

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseButtonPressed:
				for (int i = 0; i < mainMenu.size(); i++)
					if (mainMenu[i]->TestClick(Vector2(event.mouseButton.x, event.mouseButton.y))) {
						switch (i) {
						case 1:
							return;
						case 2:
							exit = true;
							return;
						}
						break;
					}
				break;
			case sf::Event::KeyPressed:
				if (event.key.code != sf::Keyboard::Key::Escape)
					break;
			case sf::Event::Closed:
				exit = true;
				return;
			}
		}
		window.clear();
		for (GUIElement* ge : mainMenu)
			ge->Draw(window);
		window.display();

		HandleGlobalSounds();
	}
}

void Game::FindMe() {
	for (auto entity : objects) {
		if (instanceof<Player>(entity))
			me = (Player*)entity;
		if (instanceof<Overlay>(entity))
			gameOver = (Overlay*)entity;
	}
}
void Game::LifeCycle(sf::RenderWindow& window) {
	bool exit = false;
	while (true) {
		MainMenu(window, exit);
		if (exit)
			return;

		_levels.front()->Generate(objects);
		FindMe();
		// objects.push_back(new Player(false));

		GameCycle(window, exit);

		// cleanup
		for (Entity* object : objects)
			delete object;
		for (Sound** sound : globalSounds)
			delete *sound;
		objects.clear();
		globalSounds.clear();

		if (exit)
			return;
	}
}
void Game::AddLevel(Level* level) {
	_levels.push_back(level);
}

Game::~Game() {
	for (auto level : _levels)
		delete level;
}