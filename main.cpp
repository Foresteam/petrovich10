#include "src/Dragger.h"
#include "src/objects/Object.h"
#include "src/objects/Player.h"
#include "src/objects/Sun.h"
#include "src/objects/Wall.h"
#include "src/objects/HealthBar.h"
#include "src/objects/Enemy.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <list>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <map>

using namespace std;

Player* me;
list<Object*> objects;
clock_t lastUpdate;
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

	if ((int)pair[0]->background + (int)pair[1]->background == 1 || pair[1]->kinematic && pair[0]->kinematic)
		return;
	Vector2 pushVec = pair[0]->hitbox.GetPushOutVector(pair[1]->hitbox);
	if (pushVec.Length() == 0)
		return;

	Vector2 push[2] = { pushVec / 2, pushVec / -2 };
	for (int i = 0; i < 2; i++)
		if (pair[i]->kinematic)
			push[i] = 0, push[(i + 1) % 2] *= 2;
	
	// if (pair[0]->mass >= pair[1]->mass) {
	// 	push[0] = pushVec * (pair[1]->mass / pair[0]->mass);
	// 	push[1] = (pushVec - push[0]) * -1;
	// }
	// else {
	// 	push[1] = pushVec * (pair[0]->mass / pair[1]->mass);
	// 	push[0] = (pushVec - push[1]) * -1;
	// }

	// Vector2 rvel = Vector2();

	for (int i = 0; i < 2; i++)
		if (!pair[i]->kinematic) {
			if (push[i].x != 0)
				pair[i]->velocity.x = 0;
			if (push[i].y != 0)
				pair[i]->velocity.y = 0;
			// printf("%s\n", pair[i]->velocity.ToString().c_str());
			pair[i]->Move(push[i]);
		}
	return;
}

void FitInScreen(Object* object) {
	if (object->GetPos().x < 0 + object->GetW() / 2) {
		object->MoveTo(Vector2(0 + object->GetW() / 2, object->GetPos().y));
		object->velocity.x = 0;
	}
	if (object->GetPos().x > window_width - object->GetW() / 2) {
		object->MoveTo(Vector2(window_width - object->GetW() / 2, object->GetPos().y));
		object->velocity.x = 0;
	}
	if (object->GetPos().y < 0 + object->GetH() / 2) {
		object->MoveTo(Vector2(object->GetPos().x, 0 + object->GetH() / 2));
		object->velocity.y = 0;
	}
	if (object->GetPos().y > window_height - object->GetH() / 2) {
		object->MoveTo(Vector2(object->GetPos().x, window_height - object->GetH() / 2));
		object->velocity.y = 0;
	}
}

void GameCycle(sf::RenderWindow& window) {
	static float renderWait = 0;
	static clock_t lastUpdate = clock();

	deltaTime = clock() / 1000.f;
	map<Object*, Object*> checkedCollision;
	list<Object*> toDelete;
	while (window.isOpen()) {
		// call update every tick
		sf::Event event;

		me->Control(window, objects);
		dragger.DoDrag(window);

		checkedCollision.clear();
		toDelete.clear();
		for (Object* object : objects) {
			if (object->Update())
				toDelete.push_back(object);
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
					if (event.key.code != sf::Keyboard::Key::Escape)
						break;
				case sf::Event::Closed:
					return;
			}
		}
		// draw all objects
		if (renderWait > 1.f / FPS) {
			window.clear();
			for (Object* o : objects)
				window.draw(o->image);
			// display everything
			window.display();

			renderWait = 0;
		}
		else
			renderWait += deltaTime;
		deltaTime = (clock() - lastUpdate) / 1000.f;
		lastUpdate = clock();

		for (Object* o : toDelete) {
			delete o;
			objects.remove(o);
		}
	}
}

int main() {
	// string ip;
	// printf("Enter host IP (or leave empty to become one): ");
	// getline(cin, ip);

	Sun* sun = new Sun();
	sun->MoveTo(Vector2(window_width / 2, sun->GetH() / 2));
	objects.push_back(sun);

	Wall* wall = new Wall();
	wall->MoveTo(Vector2(window_width - wall->GetW(), 0));
	objects.push_back(wall);

	me = new Player(true);
	objects.push_back(me);
	HealthBar* hb = new HealthBar(me, me, 1);
	objects.push_back(hb);

	Enemy* enemy = new Enemy();
	objects.push_back(enemy);
	HealthBar* ehb = new HealthBar(enemy, enemy, 1);
	objects.push_back(ehb);

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Ah sh, here we go again");
	// add sun to the list of objects
	// move sun to the center of the screen

	GameCycle(window);

	// cleanup
	for (Object* object : objects)
		delete object;
	
	return 0;
}