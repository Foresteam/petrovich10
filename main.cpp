#include "src/Dragger.h"
#include "src/objects/Object.h"
#include "src/objects/Overlay.h"
#include "src/gui/GUIElement.h"
#include "src/gui/Button.h"
#include "src/objects/Player.h"
#include "src/objects/Sun.h"
#include "src/objects/Wall.h"
#include "src/objects/HealthBar.h"
#include "src/objects/Nikita.h"
// #include "src/objects/Vadid.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
#include <unistd.h>
#include <map>
#include <random>

using namespace std;

Player* me;
Overlay* gameOver;
list<Object*> objects;
vector<GUIElement*> mainMenu;
Dragger dragger;

void Gravitate(Object* object) {
	if (object->kinematic)
		return;
	// gravitation vector. Needs some further work to work (lol)
	object->velocity += Vector2(0, 1) * (object->mass * G * deltaTime * G_SCALE);
	// printf("%s\n", object->velocity.ToString().c_str());
	object->Move(Vector2(0, object->velocity.y));
}

void Collide(Object* object1, Object* object2) {
	Object* pair[] = { object1, object2 };

	if ((int)pair[0]->background + (int)pair[1]->background == 1 || pair[1]->kinematic && pair[0]->kinematic || pair[0]->transparent || pair[1]->transparent || !pair[0]->enabled || !pair[1]->enabled)
		return;
	Vector2 pushVec = pair[0]->hitbox.GetPushOutVector(pair[1]->hitbox);
	if (pushVec.Length() == 0)
		return;

	Vector2 push[2] = { pushVec / 2, pushVec / -2 };
	for (int i = 0, j = (i + 1) % 2; i < 2; i++, j = (i + 1) % 2)
		if (pair[i]->kinematic) {
			push[i] = 0, push[j] *= 2;
			break;
		}
		// works damned as ... But it's even worse without this.
		else if (pair[i]->mass > pair[j]->mass) {
			float k = pair[j]->mass / pair[i]->mass;
			push[i] *= 2 * k;
			push[j] *= 2 * (1 - k);
		}

	for (int i = 0; i < 2; i++)
		if (!pair[i]->kinematic) {
			if (push[i].x != 0)
				pair[i]->velocity.x = 0;
			if (push[i].y != 0) {
				if (pair[i]->velocity.y > 0)
					pair[i]->onGround = true;
				pair[i]->velocity.y = 0;
			}
			pair[i]->Move(push[i]);
		}
}

void FitInScreen(Object* object) {
	if (object->GetPos().x < 0 + object->GetW() / 2) {
		object->MoveTo(Vector2(0 + object->GetW() / 2, object->GetPos().y));
		object->velocity.x = 0;
	}
	if (object->GetPos().x > WINDOW_WIDTH - object->GetW() / 2) {
		object->MoveTo(Vector2(WINDOW_WIDTH - object->GetW() / 2, object->GetPos().y));
		object->velocity.x = 0;
	}
	if (object->GetPos().y < 0 + object->GetH() / 2) {
		object->MoveTo(Vector2(object->GetPos().x, 0 + object->GetH() / 2));
		object->velocity.y = 0;
	}
	if (object->GetPos().y > WINDOW_HEIGHT - object->GetH() / 2) {
		object->onGround = true;
		object->MoveTo(Vector2(object->GetPos().x, WINDOW_HEIGHT - object->GetH() / 2));
		object->velocity.y = 0;
	}
}

double renderWait = 0;
// this clock is the fix for tremendous GPU utilizing. Alongside with FPS limiting, ofc
chrono::_V2::system_clock::time_point lastUpdate = chrono::high_resolution_clock::now();
void DeltaTime() {
	deltaTime = (chrono::high_resolution_clock::now() - lastUpdate).count() / 1.e+9;
	lastUpdate = chrono::high_resolution_clock::now();
}
bool RenderWait() {
	if (renderWait > 1.f / FPS) {
		renderWait = 0;
		return true;
	}
	else {
		renderWait += deltaTime;
		return false;
	}
}

void GameCycle(sf::RenderWindow& window, bool &exit) {
	DeltaTime();
	map<Object*, Object*> checkedCollision;
	list<Object*> toDelete;
	while (window.isOpen()) {
		sf::Event event;

		if (me) {
			me->Control(window, objects);
			dragger.DoDrag(window);
		}
		else
			gameOver->enabled = true;

		checkedCollision.clear();
		toDelete.clear();
		for (Object* object : objects) {
			if (object->Update(objects))
				toDelete.push_back(object);
			object->onGround = false; // <= the reason
		}
		// two cycles go through the same array. Nice.
		for (Object* object : objects) {
			Gravitate(object);
			for (Object* object2 : objects)
				if (object != object2 && (checkedCollision[object] != object2) && (checkedCollision[object2] != object)) {
					Collide(object, object2);
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
			for (Object* o : objects)
				o->Draw(window);
			window.display();
		}

		for (Object* o : toDelete) {
			if (o == me) {
				me = nullptr;
				dragger.Release();
			}
			delete o;
			objects.remove(o);
		}
	}
}

void MainMenu(sf::RenderWindow& window, bool& exit) {
	while (window.isOpen()) {
		DeltaTime();
		// here we limit, mostly, CPU performance, to not make it calculate the nothing that happens
		// we can do this 'cuz then we use pollEvent, that "stacks" the incoming events, 'til take pull 'em out
		if (RenderWait())
			this_thread::sleep_for(chrono::milliseconds(100));

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
	}
}

int main() {
	srand(time(0));
	// could this be... multiplayer?
	// string ip;
	// printf("Enter host IP (or leave empty to become one): ");
	// getline(cin, ip);

	wallBreakBuffer.loadFromFile("../assets/sounds/wall_break.ogg");
	wallBreakSound.setBuffer(wallBreakBuffer);

	mainMenu.push_back(new GUIElement(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), "../assets/textures/mainmenu.jpg"));
	mainMenu.push_back(new Button(Vector2(WINDOW_WIDTH / 2, 200), "../assets/textures/playbutton.png"));
	mainMenu.push_back(new Button(Vector2(WINDOW_WIDTH / 2, 500), "../assets/textures/exitbutton.png"));

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ah sh, here we go again");
	// add sun to the list of objects
	// move sun to the center of the screen

	bool exit = false;
	while (true) {
		MainMenu(window, exit);
		if (exit)
			return 0;
		Object* background = new Object("../assets/textures/game_background.jpg");
		background->background = true;
		background->kinematic = true;
		background->transparent = true;
		background->MoveTo(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
		objects.push_back(background);

		Sun* sun = new Sun();
		sun->MoveTo(Vector2(WINDOW_WIDTH / 2, sun->GetH() / 2));
		objects.push_back(sun);

		Nikita* nikita = new Nikita();
		nikita->MoveTo(Vector2(WINDOW_WIDTH - nikita->GetW() / 2, 0));
		objects.push_back(nikita);

		// Vadid* vadid = new Vadid(1);
		// vadid->MoveTo(Vector2(WINDOW_WIDTH / 2, 0));
		// objects.push_back(vadid);

		Wall* wall = new Wall();
		wall->MoveTo(Vector2(WINDOW_WIDTH - wall->GetW() / 2 - nikita->GetW(), 0));
		objects.push_back(wall);

		gameOver = new Overlay(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), "../assets/textures/game_over.png");
		gameOver->enabled = false;
		objects.push_back(gameOver);

		me = new Player(true);
		objects.push_back(me);

		GameCycle(window, exit);

		// cleanup
		for (Object* object : objects)
			delete object;
		objects.clear();

		if (exit)
			return 0;
	}
	
	return 0;
}