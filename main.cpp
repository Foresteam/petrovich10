#include "src/engine/Game.h"
#include "src/entities/Sun.h"
#include "src/entities/Wall.h"
#include "src/entities/Nikita.h"
#include "src/entities/Vadid/Rasengan.h"
#include "src/gui/Button.h"

using namespace std;

int main() {
	srand(time(0));
	Game game = Game();
	// could this be... multiplayer?
	// string ip;
	// printf("Enter host IP (or leave empty to become one): ");
	// getline(cin, ip);

	wallBreakBuffer.loadFromFile((ASSETS + "sounds/wall_break.ogg").c_str());
	wallBreakSound.setBuffer(wallBreakBuffer);

	game.mainMenu.push_back(new GUIElement(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), ASSETS + "textures/mainmenu.jpg"));
	game.mainMenu.push_back(new Button(Vector2(WINDOW_WIDTH / 2, 200), (ASSETS + "textures/playbutton.png").c_str()));
	game.mainMenu.push_back(new Button(Vector2(WINDOW_WIDTH / 2, 500), (ASSETS + "textures/exitbutton.png").c_str()));

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ah sh, here we go again");
	// add sun to the list of objects
	// move sun to the center of the screen

	game.AddLevel(new Level([game](std::list<Entity*>& entities) {
		Entity* background = new Entity(ASSETS + "textures/game_background.jpg");
		background->background = true;
		background->kinematic = true;
		background->transparent = true;
		background->MoveTo(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
		entities.push_back(background);

		Sun* sun = new Sun();
		sun->MoveTo(Vector2(WINDOW_WIDTH / 2, sun->GetH() / 2));
		entities.push_back(sun);

		Nikita* nikita = new Nikita();
		nikita->MoveTo(Vector2(WINDOW_WIDTH - nikita->GetW() / 2, 0));
		entities.push_back(nikita);

		Wall* wall = new Wall();
		wall->MoveTo(Vector2(WINDOW_WIDTH - wall->GetW() / 2 - nikita->GetW(), 0));
		entities.push_back(wall);

		entities.push_back(new Rasengan(Vector2(100, sun->GetH() / 2), Vector2(50, 25), 50));

		// Vadid* vadid = new Vadid(1);
		// vadid->MoveTo(Vector2(WINDOW_WIDTH / 2, 0));
		// entities.push_back(vadid);
		Overlay* gameOver = new Overlay(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), ASSETS + "textures/game_over.png");
		gameOver->enabled = false;
		entities.push_back(gameOver);

		Player* me = new Player(true);
		entities.push_back(me);
	}));

	game.LifeCycle(window);
	
	return 0;
}