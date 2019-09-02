#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "PlayerSelection.h"
#include "GameOver.h"
#include "Icon.h"
#include "IconManager.h"

using namespace std;
using namespace sf;

enum GameStages {
	SelectPlayers = 0,
	CurvesRunning = 1,
	GameIsOver = 2
};

int main()
{
	Font font;
	if (!font.loadFromFile("resources/arial.ttf"))	// Necessary to render text
		throw exception("Could not load font!");

	RenderWindow* window = new RenderWindow(VideoMode(800, 600), "Achtung - die Kurve!");
	window->setFramerateLimit(60);
	bool fullscreen = false;

	GameStages stage = SelectPlayers;

	PlayerSelection playerSelection = PlayerSelection(window, &font);
	IconManager itemManager = IconManager(window);

	vector<Player*> players;

	int collidedCounter = 0;
	//Create a screenshot of the game before moving
	sf::Vector2u windowSize = window->getSize();
	sf::Texture texture;
	texture.create(windowSize.x, windowSize.y);
	texture.update(*window);
	sf::Image screenshot = texture.copyToImage();

	// main loop
	while (window->isOpen())		
	{
		// Handle events
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (stage == SelectPlayers)
				playerSelection.processEvent(event);
		}



		// Controll game flow
		switch (stage) {
		case SelectPlayers:
			if (playerSelection.isFinished()) {
				players = playerSelection.getPlayers();
				itemManager.setPlayers(players);
				stage = CurvesRunning;
			}
			break;

		case CurvesRunning:
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				if (!players.at(i)->getCollided()) // Only move, if not collided
					players.at(i)->move();			
			}
			if (collidedCounter == players.size()) {
				stage = GameIsOver;
				break;
			}
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				if (!players.at(i)->getCollided()) { //Collision already happened?
					bool collision = (players.at(i)->collision(screenshot, players, windowSize));
					players.at(i)->setCollided(collision);
					if (collision) {
						players.at(i)->setScore(players.at(i)->getScore() + collidedCounter); //score ranges from 0 to amount of players-1
						collidedCounter++; //Next player gets a higher score
					}
				}
			}

			itemManager.onNewFrame();
			break;

		case GameIsOver:
			collidedCounter = 0;
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				cout << players.at(i)->getScore();
				if (players.at(i)->getScore() > 10) {
					stage = GameIsOver;
				}
				else {
					players.at(i)->nextRound();
					itemManager.reset();
					stage = CurvesRunning;
				}
			}
			break;
		}

		
		if (playerSelection.isFullscreen() && !fullscreen) {
			fullscreen = true;
			window->close();
			delete window;
			window = new RenderWindow(VideoMode::getDesktopMode(), "Achtung - die Kurve!", Style::fullscreen);
			window->setFramerateLimit(60);
		}
		else if (!playerSelection.isFullscreen() && fullscreen) {
				fullscreen = false;
				window->close();
				delete window;
				window = new RenderWindow(VideoMode(800, 600), "Achtung - die Kurve!");
				window->setFramerateLimit(60);
		}

		// Draw everything

		window->clear();

		switch (stage) {
		case SelectPlayers:
			playerSelection.draw();
			break;

		case CurvesRunning:
			itemManager.draw();
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				players.at(i)->draw(window);
			}
			break;

		case GameIsOver:
			GameOver gameover = GameOver(window, &font, players);
			gameover.draw();
			break;
		}

		window->display();
	}

	// Clear memory
	for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
		delete players.at(i); players.at(i) = NULL;
	}

	delete window; window = NULL;

	return 0;
}


